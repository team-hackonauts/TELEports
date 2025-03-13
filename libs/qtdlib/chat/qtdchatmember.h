#ifndef QTDCHATMEMBER_H
#define QTDCHATMEMBER_H

#include <QObject>
#include <QScopedPointer>
#include <QDateTime>
#include "user/qtduser.h"
#include "messages/qtdmessagesender.h"
#include "qtdchatmemberstatus.h"
#include "qtdchataction.h"

/**
 * @brief The QTdChatMember class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_member.html
 */
class QTdChatMember : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QTdMessageSender *memberId READ memberId NOTIFY chatMemberChanged)
    Q_PROPERTY(QString inviteUserId READ qmlInviteUserId NOTIFY chatMemberChanged)
    Q_PROPERTY(QDateTime joinedChatDate READ qmlJoinedChatDate NOTIFY chatMemberChanged)
    Q_PROPERTY(QTdChatMemberStatus *status READ status NOTIFY chatMemberChanged)
    // TODO: botInfo https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1bot_info.html
public:
    explicit QTdChatMember(QObject *parent = nullptr);

    QTdMessageSender *memberId() const;
    QTdUser *user() const;
    QString qmlInviteUserId() const;
    qint64 inviteUserId() const;
    QDateTime qmlJoinedChatDate() const;
    qint32 joinedChatDate() const;
    QTdChatMemberStatus *status() const;

    void unmarshalJson(const QJsonObject &json) override;
    // TODO: allow admins to set status on a member
    //    Q_INVOKABLE void setStatus();

signals:
    void chatMemberChanged();
    void userChanged();

private:
    Q_DISABLE_COPY(QTdChatMember)
    QScopedPointer<QTdMessageSender> m_memberId;
    QTdInt64 m_inviteUserId;
    QTdInt32 m_joinedChatDate;
    QScopedPointer<QTdChatMemberStatus> m_status;
};

#endif // QTDCHATMEMBER_H
