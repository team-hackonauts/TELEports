#include "qtdgetchatrequest.h"
#include "client/qtdclient.h"

QTdGetChatRequest::QTdGetChatRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chat_id(0)
{
}

QJsonObject QTdGetChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getChat" },
        { "chat_id", m_chat_id },
    };
}

void QTdGetChatRequest::setChatId(const QString &id)
{
    setChatId(id.toLong());
}
void QTdGetChatRequest::setChatId(const qint64 &id)
{
    m_chat_id = id;
}

QFuture<QTdResponse>
QTdGetChatRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::chat);
}
