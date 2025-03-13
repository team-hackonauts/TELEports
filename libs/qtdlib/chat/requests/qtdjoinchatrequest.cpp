#include "qtdjoinchatrequest.h"

QTdJoinChatRequest::QTdJoinChatRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
{
}

void QTdJoinChatRequest::setChatId(const QString &chatId)
{
    setChatId(chatId.toLongLong());
}

void QTdJoinChatRequest::setChatId(const qint64 &chatId)
{
    m_chatId = chatId;
}

QJsonObject QTdJoinChatRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "joinChat" },
        { "chat_id", m_chatId.value() }
    };
}
