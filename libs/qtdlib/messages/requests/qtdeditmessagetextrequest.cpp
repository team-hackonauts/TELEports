#include "qtdeditmessagetextrequest.h"
#include <QJsonArray>
#include "client/qtdclient.h"

QTdEditMessageTextRequest::QTdEditMessageTextRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatId(0)
    , m_messageId(0)
    , m_text(QString())
    , m_entities(QJsonArray())
{
}

void QTdEditMessageTextRequest::setText(const QString &text)
{
    m_text = text;
}

void QTdEditMessageTextRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdEditMessageTextRequest::setMessageId(const qint64 &id)
{
    m_messageId = id;
}

void QTdEditMessageTextRequest::setEntities(const QJsonArray &entities)
{
    m_entities = entities;
}

QJsonObject QTdEditMessageTextRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "editMessageText" },
        { "chat_id", m_chatId },
        { "message_id", m_messageId },
        { "input_message_content", QJsonObject{
                                           { "@type", "inputMessageText" },
                                           { "text", QJsonObject{
                                                             { "@type", "formattedText" },
                                                             { "text", m_text },
                                                             { "entities", m_entities } } },
                                           { "disable_web_page_preview", false },
                                           { "clear_draft", true } } }
    };
}

QFuture<QTdResponse> QTdEditMessageTextRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::message);
}
