#ifndef QTDGETSECRETCHATREQUEST_H
#define QTDGETSECRETCHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdGetSecretChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_secret_chat.html
 */
class QTdGetSecretChatRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdGetSecretChatRequest(QObject *parent = nullptr);

    void setSecretChatId(const qint64 &id);
    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QTdGetSecretChatRequest)
    qint64 m_chatId;
};

#endif // QTDGETSECRETCHATREQUEST_H
