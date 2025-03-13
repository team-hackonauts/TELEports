#include "qtdcheckchatinvitelinkrequest.h"
#include "client/qtdclient.h"

QTdCheckChatInviteLinkRequest::QTdCheckChatInviteLinkRequest(QObject *parent)
    : QTdRequest(parent)
    , m_inviteLink("")
{
}

void QTdCheckChatInviteLinkRequest::setInviteLink(const QString &inviteLink)
{
    if (inviteLink.startsWith("https://t.me/joinchat/") || inviteLink.startsWith("https://telegram.me/joinchat/") || inviteLink.startsWith("https://telegram.dog/joinchat/")) {
        m_inviteLink = inviteLink;
    } else {
        m_inviteLink = "https://t.me/joinchat/" + inviteLink;
    }
}

QJsonObject QTdCheckChatInviteLinkRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "checkChatInviteLink" },
        { "invite_link", m_inviteLink }
    };
}

QFuture<QTdResponse> QTdCheckChatInviteLinkRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::chatInviteLinkInfo);
}
