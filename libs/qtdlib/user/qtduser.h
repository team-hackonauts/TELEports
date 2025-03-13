#ifndef QTDUSER_H
#define QTDUSER_H

#include <QObject>
#include <QScopedPointer>
#include <QList>
#include "common/qabstractint64id.h"
#include "qtduserfullinfo.h"
#include "qtduserstatus.h"
#include "qtdprofilephoto.h"
#include "qtdusertype.h"
#include "qtdusernames.h"
#include "qtdemojistatus.h"

/**
 * @brief The QTdUser class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user.html
 */
class QTdUser : public QAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY nameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY nameChanged)
    Q_PROPERTY(QString username READ username NOTIFY nameChanged)
    Q_PROPERTY(QString fullName READ fullName NOTIFY nameChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QString initials READ initials NOTIFY initialsChanged)
    Q_PROPERTY(QString smallPhotoPath READ smallPhotoPath NOTIFY smallPhotoPathChanged)
    Q_PROPERTY(QTdUserFullInfo *fullInfo READ fullInfo WRITE setFullInfo NOTIFY fullInfoChanged)
    Q_PROPERTY(QTdUserStatus *status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QTdProfilePhoto *profilePhoto READ profilePhoto NOTIFY profilePhotoChanged)
    Q_PROPERTY(bool isVerified READ isVerified NOTIFY isVerifiedChanged)
    Q_PROPERTY(bool isMyself READ isMyself NOTIFY isMyselfChanged)
    Q_PROPERTY(bool isOnline READ isOnline NOTIFY statusChanged)
    Q_PROPERTY(bool isDeleted READ isDeleted NOTIFY isDeletedChanged)
    Q_PROPERTY(bool isBot READ isBot NOTIFY isBotChanged)
    Q_PROPERTY(QString restrictionReason READ restrictionReason NOTIFY restrictionReasonChanged)
    Q_PROPERTY(QString statusString READ statusString NOTIFY statusChanged)
    Q_PROPERTY(QTdUserType *userType READ userType NOTIFY userTypeChanged)
    Q_PROPERTY(QString languageCode READ languageCode NOTIFY languageCodeChanged)
    Q_PROPERTY(QTdEmojiStatus* emojiStatus READ emojiStatus NOTIFY dataChanged)
    Q_PROPERTY(bool isContact READ isContact NOTIFY dataChanged)
    Q_PROPERTY(bool isMutualContact READ isMutualContact NOTIFY dataChanged)
    Q_PROPERTY(bool isPremium READ isPremium NOTIFY dataChanged)
    Q_PROPERTY(bool isSupport READ isSupport NOTIFY dataChanged)
    Q_PROPERTY(bool isScam READ isScam NOTIFY dataChanged)
    Q_PROPERTY(bool isFake READ isFake NOTIFY dataChanged)
    Q_PROPERTY(bool haveAccess READ haveAccess NOTIFY dataChanged)

public:
    explicit QTdUser(QObject *parent = nullptr);

    QString firstName() const;
    QString lastName() const;
    QString username() const;
    QString fullName() const;
    QString phoneNumber() const;
    QString initials() const;
    QString smallPhotoPath() const;
    Q_INVOKABLE QString avatarColor(qint64 userId);
    QTdUserFullInfo *fullInfo();
    QTdUserStatus *status() const;
    QTdProfilePhoto *profilePhoto() const;
    bool isVerified() const;
    bool isMyself();
    bool isOnline() const;
    bool isDeleted() const;
    bool isBot() const;
    QString restrictionReason() const;
    QString statusString() const;
    QString languageCode() const;
    QTdUserType *userType() const;
    QTdEmojiStatus* emojiStatus() const;
    bool isContact() const;
    bool isMutualContact() const;
    bool isPremium() const;
    bool isSupport() const;
    bool isScam() const;
    bool isFake() const;
    bool haveAccess() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void nameChanged(QString name);
    void phoneNumberChanged(QString phoneNumber);
    void initialsChanged(QString initials);
    void smallPhotoPathChanged();
    void fullInfoChanged(QTdUserFullInfo *fullInfo);
    void statusChanged(QTdUserStatus *status);
    void profilePhotoChanged(QTdProfilePhoto *profilePhoto);
    void isVerifiedChanged(bool isVerified);
    void isMyselfChanged(bool isMyself);
    void isDeletedChanged();
    void isBotChanged();
    void restrictionReasonChanged(QString restrictionReason);
    void languageCodeChanged(QString languageCode);
    void dataChanged();
    void userTypeChanged(QTdUserType *userType);

public slots:
    void setFirstName(QString firstName);
    void setLastName(QString lastName);
    void setPhoneNumber(QString phoneNumber);
    void setFullInfo(QTdUserFullInfo *fullInfo);
    void setStatus(QTdUserStatus *status);

private:
    Q_DISABLE_COPY(QTdUser)
    QString m_firstName;
    QString m_lastName;
    QScopedPointer<QTdUsernames> m_userNames;
    QString m_phoneNumber;
    qint64 m_my_id;
    QScopedPointer<QTdUserFullInfo> m_fullInfo;
    QScopedPointer<QTdUserStatus> m_status;
    QScopedPointer<QTdProfilePhoto> m_profilePhoto;
    bool m_isVerified;
    QString m_restrictionReason;
    QString m_languageCode;
    QScopedPointer<QTdUserType> m_userType;
    QScopedPointer<QTdEmojiStatus> m_emojiStatus;
    bool m_isContact;
    bool m_isMutualContact;
    bool m_isPremium;
    bool m_isSupport;
    bool m_isScam;
    bool m_isFake;
    bool m_haveAccess;

};

#endif // QTDUSER_H
