#include "qtdforwardmessagesrequest.h"
#include "client/qtdclient.h"

QTdForwardMessagesRequest::QTdForwardMessagesRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatId(0)
    , m_fromChatId(0)
    , m_messageIds(QList<qint64>())
{
}

void QTdForwardMessagesRequest::setChatId(const qint64 chatId)
{
    m_chatId = chatId;
}

void QTdForwardMessagesRequest::setFromChatId(const qint64 fromChatId)
{
    m_fromChatId = fromChatId;
}

void QTdForwardMessagesRequest::setMessageIds(const QList<qint64> &messageIds)
{
    m_messageIds = messageIds;
}

QJsonObject QTdForwardMessagesRequest::marshalJson()
{
    QJsonArray ids;
    for (const qint64 &id : m_messageIds) {
        ids << QJsonValue(id);
    }
    return QJsonObject{
        { "@type", "forwardMessages" },
        { "chat_id", m_chatId },
        { "from_chat_id", m_fromChatId },
        { "message_ids", ids },
        { "as_album", false },
    };
}

QFuture<QTdResponse> QTdForwardMessagesRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::basicGroup);
}
