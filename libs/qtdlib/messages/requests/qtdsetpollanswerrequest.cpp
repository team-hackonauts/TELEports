#include "qtdsetpollanswerrequest.h"
#include <QJsonArray>

QTdSetPollAnswerRequest::QTdSetPollAnswerRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
    , m_messageId(0)
{
}

void QTdSetPollAnswerRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdSetPollAnswerRequest::setMessageId(const qint64 &id)
{
    m_messageId = id;
}

void QTdSetPollAnswerRequest::setPollOptions(const QList<qint32> &optionIds)
{
    m_optionIds = optionIds;
}

QJsonObject QTdSetPollAnswerRequest::marshalJson()
{
    QJsonArray json_polloptions;
    for (auto &m_optionId : m_optionIds) {
        json_polloptions.append(m_optionId);
    }
    return QJsonObject{
        { "@type", "setPollAnswer" },
        { "chat_id", m_chatId },
        { "message_id", m_messageId },
        { "option_ids", json_polloptions },
    };
}