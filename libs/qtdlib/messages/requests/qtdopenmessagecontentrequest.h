#ifndef QTDOPENMESSAGECONTENTREQUEST_H
#define QTDOPENMESSAGECONTENTREQUEST_H

#include <QObject>
#include <QJsonArray>

#include "common/qtdrequest.h"

/**
 * @brief The QTdSendMessageRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_message.html
 */
class QTdOpenMessageContentRequest : public QTdRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdOpenMessageContentRequest)
    QString m_chatId;
    QString m_messageId;

public:
    explicit QTdOpenMessageContentRequest(QObject *parent = nullptr);
    void setChatId(const QString &id);
    void setMessageId(const QString &id);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();
};

#endif // QTDOPENMESSAGECONTENTREQUEST_H
