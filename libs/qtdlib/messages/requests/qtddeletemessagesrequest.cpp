#include "qtddeletemessagesrequest.h"
#include <QJsonArray>

QTdDeleteMessagesRequest::QTdDeleteMessagesRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
    , m_revoke(true)
{
}

void QTdDeleteMessagesRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdDeleteMessagesRequest::setMessageIds(const QList<qint64> &messageIds)
{
    m_messageIds = messageIds;
}

void QTdDeleteMessagesRequest::setRevoke(const bool value)
{
    m_revoke = value;
}

QJsonObject QTdDeleteMessagesRequest::marshalJson()
{
    QJsonArray json_messages;
    for (auto &m_messageId : m_messageIds)
        json_messages.append(m_messageId);
    return QJsonObject{
        { "@type", "deleteMessages" },
        { "chat_id", m_chatId },
        { "message_ids", json_messages },
        { "revoke", m_revoke }
    };
}
