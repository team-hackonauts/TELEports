#include "qtdopenmessagecontentrequest.h"
#include <QJsonArray>
#include "client/qtdclient.h"

QTdOpenMessageContentRequest::QTdOpenMessageContentRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatId("")
    , m_messageId("")
{
}

void QTdOpenMessageContentRequest::setChatId(const QString &id)
{
    m_chatId = id;
}

void QTdOpenMessageContentRequest::setMessageId(const QString &id)
{
    m_messageId = id;
}

QJsonObject QTdOpenMessageContentRequest::marshalJson()
{

    return QJsonObject{
        { "@type", "openMessageContent" },
        { "chat_id", m_chatId },
        { "message_id", m_messageId }
    };
}

QFuture<QTdResponse> QTdOpenMessageContentRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::message);
}
