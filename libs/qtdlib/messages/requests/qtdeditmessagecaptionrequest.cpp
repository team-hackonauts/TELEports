#include "qtdeditmessagecaptionrequest.h"
#include <QJsonArray>
#include <QDebug>
#include "client/qtdclient.h"

QTdEditMessageCaptionRequest::QTdEditMessageCaptionRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatId(0)
    , m_messageId(0)
    , m_text(QString())
    , m_entities(QJsonArray())
{
}

void QTdEditMessageCaptionRequest::setText(const QString &text)
{
    m_text = text;
}

void QTdEditMessageCaptionRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdEditMessageCaptionRequest::setMessageId(const qint64 &id)
{
    m_messageId = id;
}

void QTdEditMessageCaptionRequest::setEntities(const QJsonArray &entities)
{
    m_entities = entities;
}

QJsonObject QTdEditMessageCaptionRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "editMessageCaption" },
        { "chat_id", m_chatId },
        { "message_id", m_messageId },
        { "caption", QJsonObject{
                             { "@type", "formattedText" },
                             { "text", m_text },
                             { "entities", m_entities } } },
        { "disable_web_page_preview", false },
        { "clear_draft", true }
    };
}

QFuture<QTdResponse> QTdEditMessageCaptionRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::message);
}
