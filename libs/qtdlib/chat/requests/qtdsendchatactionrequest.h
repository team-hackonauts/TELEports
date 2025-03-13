#ifndef QTDSENDCHATACTIONREQUEST_H
#define QTDSENDCHATACTIONREQUEST_H

#include "common/qtdrequest.h"
#include "chat/qtdchatactionfactory.h"
#include <QObject>

/**
 * @brief The QTdSendChatActionRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_chat_action.html
 */
class QTdSendChatActionRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;

public:
    explicit QTdSendChatActionRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    void setAction(const QTdChatAction &action);
    QJsonObject marshalJson();
};

#endif // QTDSENDCHATACTIONREQUEST_H
