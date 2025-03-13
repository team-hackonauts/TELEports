#ifndef QTDSETCHATMESSAGETTLREQUEST_H
#define QTDSETCHATMESSAGETTLREQUEST_H

#include "common/qtdrequest.h"
#include <QObject>

/**
 * @brief The QTdSetChatMessageTtlRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_chat_set_ttl_message.html
 */
class QTdSetChatMessageTtlRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    qint32 m_ttl;

public:
    explicit QTdSetChatMessageTtlRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    void setTTL(const qint32 &ttl);
    QJsonObject marshalJson();
};

#endif // QTDSETCHATMESSAGETTLREQUEST_H
