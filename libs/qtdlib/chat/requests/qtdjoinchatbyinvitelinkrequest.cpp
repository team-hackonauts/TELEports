#include "qtdjoinchatbyinvitelinkrequest.h"
#include "client/qtdclient.h"

QTdJoinChatByInviteLinkRequest::QTdJoinChatByInviteLinkRequest(QObject *parent)
    : QTdRequest(parent)
    , m_inviteLink("")
{
}

void QTdJoinChatByInviteLinkRequest::setInviteLink(const QString &inviteLink)
{
    if (inviteLink.startsWith("https://t.me/joinchat/") || inviteLink.startsWith("https://telegram.me/joinchat/") || inviteLink.startsWith("https://telegram.dog/joinchat/")) {
        m_inviteLink = inviteLink;
    } else {
        m_inviteLink = "https://t.me/joinchat/" + inviteLink;
    }
}

QJsonObject QTdJoinChatByInviteLinkRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "joinChatByInviteLink" },
        { "invite_link", m_inviteLink }
    };
}

QFuture<QTdResponse> QTdJoinChatByInviteLinkRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::chat);
}
