#include "qtdgetsecretchatrequest.h"
#include "client/qtdclient.h"

QTdGetSecretChatRequest::QTdGetSecretChatRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatId(0)
{
}

void QTdGetSecretChatRequest::setSecretChatId(const qint64 &id)
{
    m_chatId = id;
}

QJsonObject QTdGetSecretChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getSecretChat" },
        { "secret_chat_id", m_chatId },
    };
}

QFuture<QTdResponse> QTdGetSecretChatRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::secretChat);
}
