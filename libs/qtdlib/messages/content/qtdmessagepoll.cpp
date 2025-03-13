#include "qtdmessagepoll.h"

QTdMessagePoll::QTdMessagePoll(QObject *parent)
    : QTdMessageContent(parent)
    , m_poll(new QTdPoll)
{
    setType(MESSAGE_POLL);
}

QTdPoll* QTdMessagePoll::poll() {
    return m_poll.data();
}

void QTdMessagePoll::unmarshalJson(const QJsonObject &json)
{
    m_poll->unmarshalJson(json["poll"].toObject());
}