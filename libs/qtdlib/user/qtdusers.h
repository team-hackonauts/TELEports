#ifndef QTDUSERS_H
#define QTDUSERS_H

#include <QObject>
#include <QJsonObject>
#include <QPointer>
#include <QSortFilterProxyModel>
#include "user/qtduser.h"
#include "auth/qtdauthstate.h"
#include "models/QmlObjectListModel.h"

/**
 * @brief The QTdUsersSortFilterModel class
 *
 * Filters users to only show the allowed user ids
 *
 * This makes it easier to reuse the global user instance
 * to just show a subset of user.
 */
class QTdUsersSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdUsersSortFilterModel)
    Q_PROPERTY(int count READ rowCount NOTIFY rowCountChanged)
public:
    explicit QTdUsersSortFilterModel(QObject *parent = nullptr);
    Q_INVOKABLE QTdUser *get(const int &row);

public slots:
    void setAllowedUsers(QList<qint64> user_ids);

signals:
    void countChanged();
    void allowedUsersChanged();
    void rowCountChanged();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

private:
    QList<qint64> m_uids;
};

class QTdUsers : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ qmlModel NOTIFY modelChanged)
    Q_PROPERTY(QTdUser* me READ meMyself NOTIFY meMyselfChanged)
    Q_PROPERTY(QObject *contactsmodel READ qmlContactsModel NOTIFY contactsChanged)

public:
    explicit QTdUsers(QObject *parent = nullptr);
    ~QTdUsers();

    static QTdUsers *instance();

    QObject* qmlModel() const;
    QObject *qmlContactsModel() const;
    QTdUser* meMyself() const;

    QQmlObjectListModel<QTdUser> *model() const;
    QTdUsersSortFilterModel *contactsmodel() const; 

public slots:
    void deleteUser(const int &userId);
    void addUser(const QString &userName, const QString &firstName, const QString &lastName);
    void addContact(const QString &phoneNumber, const QString &firstName, const QString &lastName, const qint64 userId);    
    void handleUpdateUser(const QJsonObject &user);

signals:
    void modelChanged(QObject* model);
    void userCreated(qint64 id);
    void meMyselfChanged(QTdUser *meMyself);
    void contactsChanged();
    void contactsImported(int existingUsers, int importedContacts);

private slots:
    void handleUpdateUserStatus(const QString &userId, const QJsonObject &status);
    void handleAuthStateChanged(const QTdAuthState *state);
    void handleContacts(const QJsonObject &contacts);
    void handleUpdateUserFullInfo(const QString &userId, const QJsonObject &fullInfo);

private:
    Q_DISABLE_COPY(QTdUsers)
    QQmlObjectListModel<QTdUser> *m_model;
    QPointer<QTdUser> m_meMyself;
    QTdUsersSortFilterModel *m_contactsmodel;
    QList<qint64> m_contact_ids;
    void getAllContacts();
};

#endif // QTDUSERS_H
