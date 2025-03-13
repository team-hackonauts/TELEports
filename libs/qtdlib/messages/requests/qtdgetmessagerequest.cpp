#include "qtdgetmessagerequest.h"
#include "client/qtdclient.h"

QTdGetMessageRequest::QTdGetMessageRequest(QObject *parent)
    : QTdRequest(parent)
{
}

void QTdGetMessageRequest::setChatId(const qint64 &chat)
{
    m_chat = chat;
}

void QTdGetMessageRequest::setMessageId(const qint64 &msg)
{
    m_msg = msg;
}

QJsonObject QTdGetMessageRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getMessage" },
        { "chat_id", m_chat },
        { "message_id", m_msg },
    };
}

QFuture<QTdResponse> QTdGetMessageRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::message);
}
