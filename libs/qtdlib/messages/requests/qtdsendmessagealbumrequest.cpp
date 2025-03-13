#include "qtdsendmessagealbumrequest.h"
#include <QJsonArray>
#include <QList>
#include "client/qtdclient.h"

QTdSendMessageAlbumRequest::QTdSendMessageAlbumRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatId(0)
    , m_replyMessageId(0)
    , m_contents(QList<QTdInputMessageContent*>())
    , m_messageSendOptions(new QTdMessageSendOptions)
{
}

void QTdSendMessageAlbumRequest::setContents(QList<QTdInputMessageContent*> &contents)
{
    m_contents = contents;
}

void QTdSendMessageAlbumRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdSendMessageAlbumRequest::setReplyToMessageId(const qint64 &id)
{
    m_replyMessageId = id;
}

void QTdSendMessageAlbumRequest::setDisableNotification(const bool value)
{
    m_messageSendOptions->setDisableNotifications(value);
}

void QTdSendMessageAlbumRequest::setSendDate(const qint32 value)
{
    m_messageSendOptions->setSendDate(value);
}

QJsonObject QTdSendMessageAlbumRequest::marshalJson()
{
    QJsonArray contents;
    for (int i = 0; i < m_contents.count(); ++i) {
        contents << m_contents.at(i)->marshalJson();
    }
    return QJsonObject {
        { "@type", "sendMessageAlbum" },
        { "chat_id", m_chatId },
        { "reply_to_message_id", m_replyMessageId },
        { "input_message_contents", contents },
        { "options", m_messageSendOptions->marshalJson() }
    };
}

QFuture<QTdResponse> QTdSendMessageAlbumRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::message);
}
