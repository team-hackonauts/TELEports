#include "qtdusers.h"
#include <QPointer>
#include <QDebug>
#include "client/qtdclient.h"
#include "common/qtdint.h"
#include "qtduserstatusfactory.h"
#include "requests/qtdgetcontactsrequest.h"
#include "requests/qtdremovecontactsrequest.h"
#include "requests/qtdimportcontactsrequest.h"
#include "utils/await.h"
#include "requests/qtdgetuserrequest.h"

QTdUsers::QTdUsers(QObject *parent)
    : QObject(parent)
    , m_model(Q_NULLPTR)
    , m_contactsmodel(new QTdUsersSortFilterModel)
    , m_meMyself(Q_NULLPTR)
{
    m_model = new QQmlObjectListModel<QTdUser>(this, "", "id");
    m_contactsmodel->setSourceModel(m_model);
    m_meMyself = new QTdUser(this);
    connect(QTdClient::instance(), &QTdClient::updateUser, this, &QTdUsers::handleUpdateUser);
    connect(QTdClient::instance(), &QTdClient::updateUserStatus, this, &QTdUsers::handleUpdateUserStatus);
    connect(QTdClient::instance(), &QTdClient::authStateChanged, this, &QTdUsers::handleAuthStateChanged);
    connect(QTdClient::instance(), &QTdClient::updateUserFullInfo, this, &QTdUsers::handleUpdateUserFullInfo);
}

QTdUsers::~QTdUsers()
{
    m_model->clear();
}

QObject *QTdUsers::qmlModel() const
{
    return m_model;
}

QObject *QTdUsers::qmlContactsModel() const
{
    return m_contactsmodel;
}

QQmlObjectListModel<QTdUser> *QTdUsers::model() const
{
    return m_model;
}

QTdUsersSortFilterModel *QTdUsers::contactsmodel() const
{
    return m_contactsmodel;
}

static QPointer<QTdUsers> s_users;
QTdUsers *QTdUsers::instance()
{
    if (s_users.isNull()) {
        s_users = new QTdUsers();
    }
    return s_users;
}

QTdUser *QTdUsers::meMyself() const
{
    return m_meMyself;
}

void QTdUsers::addUser(const QString &userName, const QString &firstName, const QString &lastName)
{
    qWarning() << "Trying to find and add user" << userName << firstName << lastName;
    QScopedPointer<QTdContact> newContact(new QTdContact);
    newContact->setPhoneNumber(userName);
    newContact->setFirstName(firstName);
    newContact->setLastName(lastName);
    QScopedPointer<QTdImportContactsRequest> importContactsReq(new QTdImportContactsRequest());
    QList<QTdContact *> contacts;
    contacts.append(newContact.data());
    importContactsReq->setContacts(contacts);
    QFuture<QTdResponse> resp = importContactsReq->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Failed to import contacts with error: " << resp.result().errorString();
        return;
    }
    QJsonObject result = resp.result().json();
    auto existingUsers = result["user_ids"].toArray();
    auto importedContacts = (int)result["importer_count"].toDouble();
    emit contactsImported(existingUsers.count(), importedContacts);
    getAllContacts();
}

void QTdUsers::addContact(const QString &phoneNumber, const QString &firstName, const QString &lastName, const qint64 userId) {
    QScopedPointer<QTdContact> newContact(new QTdContact);
    newContact->setPhoneNumber(phoneNumber);
    newContact->setFirstName(firstName);
    newContact->setLastName(lastName);
    newContact->setUserId(userId);
    QJsonObject addContactRequest = QJsonObject {
        { "@type", "addContact" },
        { "contact", newContact->marshalJson() }
    };
    QTdClient::instance()->send(addContactRequest);
}

void QTdUsers::deleteUser(const int &userId)
{
    QList<qint64> deleteUserIds;
    deleteUserIds.append(userId);
    QScopedPointer<QTdRemoveContactsRequest> deleteUserReq(new QTdRemoveContactsRequest);
    deleteUserReq->setUserIds(deleteUserIds);
    QFuture<QTdResponse> resp = deleteUserReq->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Failed to get contacts with error: " << resp.result().errorString();
        return;
    }
    getAllContacts();
}

void QTdUsers::handleUpdateUser(const QJsonObject &user)
{
    const qint64 uid = user["id"].toVariant().toLongLong();
    // Need to remember the model actually indexes on the qmlId variant which is a QString
    QTdUser *tduser = m_model->getByUid(QString::number(uid));
    if (!tduser) {
        tduser = new QTdUser();
        tduser->unmarshalJson(user);
        m_model->append(tduser);
        emit userCreated(uid);
    } else {
        tduser->unmarshalJson(user);
    }

    const qint64 myId = QTdClient::instance()->getOption("my_id").toLongLong();
    if (uid == myId) {
        m_meMyself->unmarshalJson(user);
        emit meMyselfChanged(m_meMyself);
    }
}

void QTdUsers::handleUpdateUserStatus(const QString &userId, const QJsonObject &status)
{
    QTdUser *tduser = m_model->getByUid(userId);
    if (tduser) {
        tduser->setStatus(QTdUserStatusFactory::create(status, tduser));
    }

    const qint64 uid = userId.toLongLong();
    const qint64 myId = QTdClient::instance()->getOption("my_id").toLongLong();
    if (uid == myId) {
        m_meMyself->setStatus(QTdUserStatusFactory::create(status, m_meMyself));
    }
}

void QTdUsers::getAllContacts()
{
    QScopedPointer<QTdGetContactsRequest> req(new QTdGetContactsRequest);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Failed to get contacts with error: " << resp.result().errorString();
        return;
    }
    handleContacts(resp.result().json());
}

void QTdUsers::handleAuthStateChanged(const QTdAuthState *state)
{
    switch (state->type()) {
        case QTdAuthState::Type::AUTHORIZATION_STATE_READY: {
            getAllContacts();
            break;
        }
        case QTdAuthState::Type::AUTHORIZATION_STATE_CLOSED: {
            m_model->clear();
            break;
        }
    }
}

void QTdUsers::handleContacts(const QJsonObject &contacts)
{
    const QJsonArray contactlist = contacts["user_ids"].toArray();
    QScopedPointer<QTdGetUserRequest> getUserReq(new QTdGetUserRequest);
    m_contact_ids.clear();
    for (const QJsonValue &contact : contactlist) {
        qint64 contactId = contact.toVariant().toLongLong();
        QTdUser *contactObj = m_model->getByUid(QString::number(contactId));
        m_contact_ids.append(contactId);
        if (!contactObj) {
            qWarning() << "Trying to load missing contact:" << contactId;
            getUserReq->setUserId(contactId);
            getUserReq->sendAsync();
        }
    }
    m_contactsmodel->setAllowedUsers(m_contact_ids);
    emit contactsChanged();
}

void QTdUsers::handleUpdateUserFullInfo(const QString &userId, const QJsonObject &fullInfo)
{
    QTdUser *tduser = m_model->getByUid(userId);
    if (tduser) {
        tduser->fullInfo()->unmarshalJson(fullInfo);
    }
}

QTdUsersSortFilterModel::QTdUsersSortFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    sort(0, Qt::AscendingOrder);
    connect(this, &QTdUsersSortFilterModel::countChanged, this, &QTdUsersSortFilterModel::rowCountChanged);
}

QTdUser *QTdUsersSortFilterModel::get(const int &row)
{
    QModelIndex idx = index(row, 0);
    if (idx.isValid()) {
        QModelIndex srcIdx = mapToSource(idx);
        if (srcIdx.isValid()) {
            QQmlObjectListModel<QTdUser> *model = static_cast<QQmlObjectListModel<QTdUser> *>(sourceModel());
            return model->at(srcIdx.row());
        }
    }
    return nullptr;
}

void QTdUsersSortFilterModel::setAllowedUsers(QList<qint64> user_ids)
{
    if (user_ids == m_uids) {
        return;
    }
    m_uids = user_ids;
    emit allowedUsersChanged();
    invalidateFilter();
}

bool QTdUsersSortFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QQmlObjectListModel<QTdUser> *model = static_cast<QQmlObjectListModel<QTdUser> *>(sourceModel());
    QTdUser *user = model->at(source_row);
    if (!user) {
        return false;
    }
    auto filtered = m_uids.contains(user->id());
    return filtered;
}

bool QTdUsersSortFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    QQmlObjectListModel<QTdUser> *model = static_cast<QQmlObjectListModel<QTdUser> *>(sourceModel());
    QTdUser *left = model->at(source_left.row());
    QTdUser *right = model->at(source_right.row());

    QString compareStringLeft = !left->firstName().isEmpty()
            ? left->firstName()
            : !left->lastName().isEmpty()
                    ? left->lastName()
                    : left->username();

    QString compareStringRight = !right->firstName().isEmpty()
            ? right->firstName()
            : !right->lastName().isEmpty()
                    ? right->lastName()
                    : right->username();
    auto result = QString::localeAwareCompare(compareStringLeft, compareStringRight) < 0;
    return result;
}
