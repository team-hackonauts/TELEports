#ifndef QTDCHATINVITELINKINFO_H
#define QTDCHATINVITELINKINFO_H

#include <QObject>
#include "common/qtdrequest.h"
#include "qtdchat.h"
#include "user/qtduser.h"

/**
 * @brief The QTdChatInviteLinkInfo class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_invite_link_info.html
 */
class QTdChatInviteLinkInfo : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString inviteLink READ inviteLink NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString chatId READ qmlChatId NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QObject *type READ type NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString title READ title NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QObject *photo READ photo NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString memberCount READ qmlMemberCount NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QObject *memberUsers READ memberUsers NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(bool isPublic READ isPublic NOTIFY chatInviteLinkInfoChanged)
    // These aren't original properties of the tdlib message class but we can
    // can make life easier for use in QML.
    Q_PROPERTY(QString initials READ initials NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString avatarColor READ avatarColor NOTIFY chatInviteLinkInfoChanged)
    Q_PROPERTY(QString highlightedMemberCount READ highlightedMemberCount NOTIFY chatInviteLinkInfoChanged)
public:
    explicit QTdChatInviteLinkInfo(QObject *parent = nullptr);

    QString inviteLink() const;
    qint64 chatId() const;
    QString qmlChatId() const;
    QTdChatType *type() const;
    QString title() const;
    QTdChatPhoto *photo() const;
    qint32 memberCount() const;
    QString qmlMemberCount() const;
    QQmlObjectListModel<QTdUser> *memberUsers() const;
    QList<qint64> memberUserIds() const;
    bool isPublic() const;

    QString initials() const;
    QString highlightedMemberCount() const;
    QString avatarColor() const;

    void unmarshalJson(QJsonObject &json);

signals:
    void chatInviteLinkInfoChanged();

private:
    QString m_inviteLink;
    QTdInt64 m_chatId;
    QScopedPointer<QTdChatType> m_type;
    QString m_title;
    QScopedPointer<QTdChatPhoto> m_photo;
    QTdInt32 m_memberCount;
    QScopedPointer<QQmlObjectListModel<QTdUser>> m_memberUsers;
    QList<qint64> m_memberUserIds;
    bool m_isPublic;

    QString m_initials;
    QString m_avatarColor;
    QTdInt32 m_highlightedMemberCount;
};

#endif // QTDCHATINVITELINKINFO_H
