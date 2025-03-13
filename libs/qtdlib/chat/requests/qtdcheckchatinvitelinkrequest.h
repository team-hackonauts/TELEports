#ifndef QTDCHECKCHATINVITELINKREQUEST_H
#define QTDCHECKCHATINVITELINKREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdCheckChatInviteLinkRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1check_chat_invite_link.html
 */
class QTdCheckChatInviteLinkRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdCheckChatInviteLinkRequest(QObject *parent = nullptr);

    void setInviteLink(const QString &inviteLink);

    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();

private:
    QString m_inviteLink;
};

#endif // QTDCHECKCHATINVITELINKREQUEST_H
