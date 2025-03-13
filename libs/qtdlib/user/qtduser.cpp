#include "utils/i18n.h"
#include "qtduser.h"
#include "qtduserstatusfactory.h"
#include "common/qtdhelpers.h"
#include "client/qtdclient.h"
#include "requests/qtdgetuserfullinforequest.h"
#include "utils/await.h"

QTdUser::QTdUser(QObject *parent)
    : QAbstractInt64Id(parent)
    , m_fullInfo(new QTdUserFullInfo)
    , m_status(Q_NULLPTR)
    , m_profilePhoto(new QTdProfilePhoto)
    , m_isVerified(false)
    , m_userType(Q_NULLPTR)
    , m_userNames(Q_NULLPTR)
    , m_emojiStatus(new QTdEmojiStatus)
{
    setType(USER);
    m_my_id = QTdClient::instance()->getOption("my_id").toLongLong();
}

void QTdUser::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    setFirstName(json["first_name"].toString());
    setLastName(json["last_name"].toString());
    m_userNames.reset(new QTdUsernames(this));
    m_userNames->unmarshalJson(json["usernames"].toObject());
    setPhoneNumber(json["phone_number"].toString());
    setStatus(QTdUserStatusFactory::create(json["status"].toObject(), this));
    m_isVerified = json["is_verified"].toBool();
    emit isVerifiedChanged(m_isVerified);
    m_restrictionReason = json["restriction_reason"].toString();
    emit restrictionReasonChanged(m_restrictionReason);
    m_languageCode = json["language_code"].toString();
    emit languageCodeChanged(m_languageCode);

    const QJsonObject typeObj = json["type"].toObject();
    const QString type = typeObj["@type"].toString();
    if (type == "userTypeRegular") {
        setType(USER_TYPE_REGULAR);
        m_userType.reset(new QTdUserTypeRegular(this));
    } else if (type == "userTypeBot") {
        m_userType.reset(new QTdUserTypeBot(this));
    } else if (type == "userTypeDeleted") {
        m_userType.reset(new QTdUserTypeDeleted(this));
        setFirstName("");
        setLastName("");
        emit isDeletedChanged();
    } else if (type == "userTypeUnknown") {
        m_userType.reset(new QTdUserTypeUnknown(this));
    } else {
        m_userType.reset();
    }
    if (m_userType) {
        m_userType->unmarshalJson(typeObj);
    }

    m_profilePhoto->unmarshalJson(json["profile_photo"].toObject());
    emit profilePhotoChanged(m_profilePhoto.data());
    const bool hasProfilePhoto = m_profilePhoto->small()->id() > 0;
    const bool needsDownload = m_profilePhoto->small()->local()->path().isEmpty();
    if (hasProfilePhoto && needsDownload) {
        m_profilePhoto->small()->downloadFile();
    }

    m_emojiStatus.reset(new QTdEmojiStatus(this));
    m_emojiStatus->unmarshalJson(json["emoji_status"].toObject());
    m_isContact = json["is_contact"].toBool();
    m_isMutualContact = json["is_mutual_contact"].toBool();
    m_isPremium = json["is_premium"].toBool();
    m_isSupport = json["is_support"].toBool();
    m_isScam = json["is_scam"].toBool();
    m_isFake = json["is_fake"].toBool();
    m_haveAccess = json["have_access"].toBool();

    QAbstractInt64Id::unmarshalJson(json);

    emit dataChanged();
}

QTdUserType *QTdUser::userType() const
{
    return m_userType.data();
}

QString QTdUser::restrictionReason() const
{
    return m_restrictionReason;
}

QString QTdUser::languageCode() const
{
    return m_languageCode;
}

bool QTdUser::isVerified() const
{
    return m_isVerified;
}

bool QTdUser::isMyself()
{
    if (m_my_id == 0) {
        m_my_id = QTdClient::instance()->getOption("my_id").toLongLong();
    }
    return id() == m_my_id;
}

bool QTdUser::isOnline() const
{
    return m_status->typeString() == "userStatusOnline";
}

bool QTdUser::isDeleted() const
{
    return qobject_cast<QTdUserTypeDeleted*>(m_userType.data());
}

bool QTdUser::isBot() const
{
    return qobject_cast<QTdUserTypeBot*>(m_userType.data());
}

QTdProfilePhoto *QTdUser::profilePhoto() const
{
    return m_profilePhoto.data();
}

QTdUserFullInfo *QTdUser::fullInfo()
{
    return m_fullInfo.data();
}

QTdUserStatus *QTdUser::status() const
{
    return m_status.data();
}

void QTdUser::setFirstName(QString firstName)
{
    if (m_firstName == firstName)
        return;

    m_firstName = firstName;
    emit nameChanged(m_firstName);
}

void QTdUser::setLastName(QString lastName)
{
    if (m_lastName == lastName)
        return;

    m_lastName = lastName;
    emit nameChanged(m_lastName);
}

void QTdUser::setPhoneNumber(QString phoneNumber)
{
    if (m_phoneNumber == phoneNumber)
        return;

    m_phoneNumber = phoneNumber;
    emit phoneNumberChanged(m_phoneNumber);
}

void QTdUser::setFullInfo(QTdUserFullInfo *fullInfo)
{
    m_fullInfo.reset(fullInfo);
    emit fullInfoChanged(m_fullInfo.data());
}

void QTdUser::setStatus(QTdUserStatus *status)
{
    QString oldStatusString = "";

    if (m_status) {
        oldStatusString = m_status->toString();
    }

    m_status.reset(status);
    emit statusChanged(m_status.data());

    if (m_status->toString() != oldStatusString) {
        emit m_status->statusStringChanged(m_status->toString());
    }
}

QString QTdUser::firstName() const
{
    return m_firstName;
}

QString QTdUser::lastName() const
{
    return m_lastName;
}

QString QTdUser::username() const
{
    return m_userNames->editableUsername();
}

QString QTdUser::fullName() const
{
    if (isDeleted()) {
        return gettext("Deleted User");
    }
    if (m_firstName != "") {
        auto fullName = m_firstName;
        if (m_lastName != "")
            fullName = fullName + " " + m_lastName;
        return fullName;
    } else {
        return m_userNames->editableUsername();
    }
}

QString QTdUser::phoneNumber() const
{
    return m_phoneNumber;
}

QString QTdUser::initials() const
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
    if (m_userNames->editableUsername() != "") {
        return m_userNames->editableUsername().trimmed().left(2).toUpper();
    }
    return "";
}

QString QTdUser::smallPhotoPath() const {
    if (isDeleted()) {
        return "image://theme/account";
    }
    return m_profilePhoto->smallPhotoPath();
}

QString QTdUser::statusString() const {
    if (isBot()) {
        return gettext("Bot");
    }
    return m_status->toString();
}

QString QTdUser::avatarColor(qint64 userId)
{
    return QTdHelpers::avatarColor(userId);
}

QTdEmojiStatus* QTdUser::emojiStatus() const {
    return m_emojiStatus.data();
}

bool QTdUser::isContact() const {
    return m_isContact;
}

bool QTdUser::isMutualContact() const {
    return m_isMutualContact;
}

bool QTdUser::isPremium() const {
    return m_isPremium;
}

bool QTdUser::isSupport() const {
    return m_isSupport;
}

bool QTdUser::isScam() const {
    return m_isScam;
}

bool QTdUser::isFake() const {
    return m_isFake;
}

bool QTdUser::haveAccess() const {
    return m_haveAccess;
}
