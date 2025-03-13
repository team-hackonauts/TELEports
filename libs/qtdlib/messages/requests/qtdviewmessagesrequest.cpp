#include "qtdviewmessagesrequest.h"
#include <QJsonArray>

QTdViewMessagesRequest::QTdViewMessagesRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
{
}

void QTdViewMessagesRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdViewMessagesRequest::setMessageIds(const QList<qint64> &messageIds)
{
    m_messageIds = messageIds;
}

QJsonObject QTdViewMessagesRequest::marshalJson()
{
    QJsonArray json_messages;
    for (auto &m_messageId : m_messageIds)
        json_messages.append(m_messageId);
    return QJsonObject{
        { "@type", "viewMessages" },
        { "chat_id", m_chatId },
        { "message_ids", json_messages },
        { "force_read", false }
    };
}
