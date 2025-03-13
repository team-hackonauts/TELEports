#include "qtdleavechatrequest.h"

QTdLeaveChatRequest::QTdLeaveChatRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
{
}

void QTdLeaveChatRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QTdLeaveChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "leaveChat" },
        { "chat_id", m_chatId }
    };
}
