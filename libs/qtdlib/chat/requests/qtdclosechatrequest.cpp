#include "qtdclosechatrequest.h"

QTdCloseChatRequest::QTdCloseChatRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
{
}

void QTdCloseChatRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QTdCloseChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "closeChat" },
        { "chat_id", m_chatId }
    };
}
