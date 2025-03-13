#include "qtdsetchatmessagettlrequest.h"

QTdSetChatMessageTtlRequest::QTdSetChatMessageTtlRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
{
}

void QTdSetChatMessageTtlRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdSetChatMessageTtlRequest::setTTL(const qint32 &ttl)
{
    m_ttl = ttl;
}

QJsonObject QTdSetChatMessageTtlRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "setChatMessageTtl" },
        { "chat_id", m_chatId },
        { "ttl", m_ttl }
    };
}
