#ifndef QTDCREATENEWSECRETCHATREQUEST_H
#define QTDCREATENEWSECRETCHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdCloseChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close_chat.html
 */
class QTdCreateNewSecretChatRequest : public QTdRequest
{
    Q_OBJECT
    qint64 m_userId;

public:
    explicit QTdCreateNewSecretChatRequest(QObject *parent = nullptr);

    /**
     * @brief setChatId
     * @param id of chat to close
     */
    void setUserId(const qint64 &id);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();
};

#endif // QTDCREATESECRETCHATREQUEST_H
