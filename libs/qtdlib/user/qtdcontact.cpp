#include "qtdcontact.h"

#include <QVariant>
#include <QDebug>
#include <QScopedPointer>

#include "qtdusers.h"
#include "requests/qtdsearchuserbyphonenumberrequest.h"
#include "utils/asyncfuture.h"

QTdContact::QTdContact(QObject *parent)
    : QTdObject(parent)
    , m_user(Q_NULLPTR)
    , m_firstName("")
    , m_lastName("")
    , m_phoneNumber("")
    , m_vcard("")
    , m_userId(0)
{
    setType(CONTACT);
}

QString QTdContact::firstName() const
{
    return m_firstName;
}

void QTdContact::setFirstName(QString value)
{
    m_firstName = value;
}

QString QTdContact::lastName() const
{
  return m_lastName;
}

void QTdContact::setLastName(QString value)
{
    m_lastName = value;
}

QString QTdContact::phoneNumber() const
{
    return m_phoneNumber;
}

void QTdContact::setPhoneNumber(QString value)
{
    m_phoneNumber = value;
}

QString QTdContact::vcard() const
{
    return m_vcard;
}

void QTdContact::setVcard(QString value)
{
    m_vcard = value;
}

qint64 QTdContact::userId() const
{
    return m_userId;
}

void QTdContact::setUserId(qint64 value)
{
    m_userId = value;
}

QTdUser *QTdContact::user() const {
    return m_user;
}

QString QTdContact::initials() const
{
    if (m_firstName != "") {
        if (m_lastName != "") {
            return (m_firstName.trimmed().left(1) + m_lastName.trimmed().left(1)).toUpper();
        }
        return m_firstName.trimmed().left(2).toUpper();
    }
    if (m_lastName != "") {
        return m_lastName.trimmed().left(2).toUpper();
    }
    return "";
}

void QTdContact::getUserFromModel(qint64 userId) {
    auto user = QTdUsers::instance()->model()->getByUid(QString::number(userId));
    if (user) {
        m_userId = userId;
        m_user = user;
        emit userChanged();
    }
}

void QTdContact::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_firstName = json["first_name"].toString();
    m_lastName = json["last_name"].toString();
    m_phoneNumber = json["phone_number"].toString();
    m_vcard = json["vcard"].toString();
    getUserFromModel(json["user_id"].toVariant().toLongLong());
    if (!m_user) {
        qWarning() << "QTdContact: User was not found in users datamodel, trying to search on Telegram server...";
        QScopedPointer<QTdSearchUserByPhoneNumberRequest> req(new QTdSearchUserByPhoneNumberRequest());
        req->setPhoneNumber(m_phoneNumber);
        auto future = req->sendAsync();
        AsyncFuture::observe(future).subscribe([this](QTdResponse resp) {
            if (resp.isError()) {
                auto errorMessage = resp.errorString();
                qWarning() << "Error:" << errorMessage;
                return;
            }
            auto id = resp.json()["id"].toVariant().toLongLong();
            QTdUsers::instance()->handleUpdateUser(resp.json());
            getUserFromModel(id);
        });
    }
    emit dataChanged();
}

QJsonObject QTdContact::marshalJson() {
    return QJsonObject{
        { "@type", "contact" },
        { "first_name", m_firstName },
        { "last_name", m_lastName },
        { "phone_number", m_phoneNumber },
        { "vcard", m_vcard },
        { "user_id", m_userId }
    };
}
