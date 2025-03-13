#include "qtdsetchatdraftrequest.h"
#include <QJsonArray>
#include "client/qtdclient.h"
#include "messages/qtddraftmessage.h"

QTdSetChatDraftRequest::QTdSetChatDraftRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatId(0)
    , m_draftMessage(new QTdDraftMessage)
{
}

void QTdSetChatDraftRequest::setDraftMessage(QTdDraftMessage *draftMessage)
{
    m_draftMessage.reset(draftMessage);
}

void QTdSetChatDraftRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QTdSetChatDraftRequest::marshalJson()
{

    return QJsonObject {
        { "@type", "setChatDraftMessage" },
        { "chat_id", m_chatId },
        { "draft_message", m_draftMessage->marshalJson() }
    };
}

QFuture<QTdResponse> QTdSetChatDraftRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::chat);
}
