#ifndef QTDFORWARDMESSAGESREQUEST_H
#define QTDFORWARDMESSAGESREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdMessagesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1forward_messages.html
 */
class QTdForwardMessagesRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdForwardMessagesRequest(QObject *parent = nullptr);

    void setChatId(const qint64 chatId);
    void setFromChatId(const qint64 fromChatId);
    void setMessageIds(const QList<qint64> &messageIds);

    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QTdForwardMessagesRequest)
    qint64 m_chatId, m_fromChatId;
    QList<qint64> m_messageIds;
};

#endif // QTDFORWARDMESSAGESREQUEST_H