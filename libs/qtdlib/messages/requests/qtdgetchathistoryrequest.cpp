#include "qtdgetchathistoryrequest.h"
#include "client/qtdclient.h"

QTdGetChatHistoryRequest::QTdGetChatHistoryRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatId(0)
    , m_fromMessageId(0)
    , m_offset(0)
    , m_limit(0)
    , m_onlyLocal(false)
{
}

void QTdGetChatHistoryRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdGetChatHistoryRequest::setFromMessageId(const qint64 &fromMessageId)
{
    m_fromMessageId = fromMessageId;
}

void QTdGetChatHistoryRequest::setOffset(const qint32 &offset)
{
    m_offset = offset;
}

void QTdGetChatHistoryRequest::setLimit(const qint32 &limit)
{
    m_limit = limit;
}

void QTdGetChatHistoryRequest::setOnlyLocal(const bool value)
{
    m_onlyLocal = value;
}

QJsonObject QTdGetChatHistoryRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getChatHistory" },
        { "chat_id",  m_chatId },
        { "from_message_id", m_fromMessageId },
        { "offset", m_offset },
        { "limit", m_limit },
        { "only_local", m_onlyLocal }
    };
}

QFuture<QTdResponse> QTdGetChatHistoryRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::messages);
}
