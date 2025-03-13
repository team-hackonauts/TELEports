#include "qtdsendmessagerequest.h"
#include <QJsonArray>
#include "client/qtdclient.h"

QTdSendMessageRequest::QTdSendMessageRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatId(0)
    , m_replyMessageId(0)
    , m_content(Q_NULLPTR)
    , m_messageSendOptions(new QTdMessageSendOptions)
{
}

void QTdSendMessageRequest::setContent(QTdInputMessageContent *content)
{
    m_content = content;
}

void QTdSendMessageRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdSendMessageRequest::setReplyToMessageId(const qint64 &id)
{
    m_replyMessageId = id;
}

void QTdSendMessageRequest::setDisableNotification(const bool value)
{
    m_messageSendOptions->setDisableNotifications(value);
}

void QTdSendMessageRequest::setSendDate(const qint32 value)
{
    m_messageSendOptions->setSendDate(value);
}

QJsonObject QTdSendMessageRequest::marshalJson()
{

    return QJsonObject{
        { "@type", "sendMessage" },
        { "chat_id", m_chatId },
        { "reply_to_message_id", m_replyMessageId },
        { "input_message_content", m_content->marshalJson() },
        { "options", m_messageSendOptions->marshalJson() }
    };
}

QFuture<QTdResponse> QTdSendMessageRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::message);
}
