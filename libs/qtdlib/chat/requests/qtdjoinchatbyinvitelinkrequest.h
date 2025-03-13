#ifndef QTDJOINCHATBYINVITELINKREQUEST_H
#define QTDJOINCHATBYINVITELINKREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdJoinChatByInviteLinkRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1join_chat_by_invite_link.html
 */
class QTdJoinChatByInviteLinkRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdJoinChatByInviteLinkRequest(QObject *parent = nullptr);

    /**
     * @brief Invite link to import; should begin with "https://t.me/joinchat/", "https://telegram.me/joinchat/", or "https://telegram.dog/joinchat/".
     */
    void setInviteLink(const QString &inviteLink);

    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();

private:
    QString m_inviteLink;
};

#endif // QTDJOINCHATBYINVITELINKREQUEST_H
