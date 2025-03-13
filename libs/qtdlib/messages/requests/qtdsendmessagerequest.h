#ifndef QTDSENDMESSAGEREQUEST_H
#define QTDSENDMESSAGEREQUEST_H

#include <QObject>
#include <QJsonArray>
#include <QScopedPointer>

#include "common/qtdrequest.h"
#include "qtdinputmessagecontent.h"
#include "qtdmessagesendoptions.h"

/**
 * @brief The QTdSendMessageRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_message.html
 */
class QTdSendMessageRequest : public QTdRequest
{
    Q_OBJECT

public:
    explicit QTdSendMessageRequest(QObject *parent = nullptr);
    void setContent(QTdInputMessageContent *content);
    void setChatId(const qint64 &id);
    void setReplyToMessageId(const qint64 &id);
    void setDisableNotification(const bool value);
    void setSendDate(const qint32 value);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QTdSendMessageRequest)
    qint64 m_chatId;
    qint64 m_replyMessageId;
    QTdInputMessageContent *m_content;
    QScopedPointer<QTdMessageSendOptions> m_messageSendOptions;

};

#endif // QTDSENDMESSAGEREQUEST_H
