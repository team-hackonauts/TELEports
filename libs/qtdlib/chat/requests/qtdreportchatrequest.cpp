#include "qtdreportchatrequest.h"
#include <QJsonArray>

QTdReportChatRequest::QTdReportChatRequest(QObject *parent)
    : QTdOkRequest(parent)
{
}

void QTdReportChatRequest::setChatId(const QString &id) {
    m_chatId = id;
}

void QTdReportChatRequest::setMessageIds(const QList<qint64> &messageIds) {
    m_messageIds = messageIds;
}

void QTdReportChatRequest::setReason(QTdChatReportReason *reason) {
    m_reason = reason;
}

void QTdReportChatRequest::setText(const QString &text) {
    m_text = text;
}

QJsonObject QTdReportChatRequest::marshalJson()
{
    QJsonArray json_messages;
    for (auto &m_messageId : m_messageIds)
        json_messages.append(m_messageId);
    return QJsonObject{
        { "@type", "reportChat" },
        { "chat_id", m_chatId },
        { "message_ids", json_messages },
        { "reason", m_reason->marshalJson() },
        { "text", m_text }
    };
}