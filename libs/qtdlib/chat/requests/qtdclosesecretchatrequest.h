#ifndef QTDCLOSESECRETCHATREQUEST_H
#define QTDCLOSESECRETCHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdCloseSecretChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close_secret_chat.html
 */
class QTdCloseSecretChatRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_secretChatId;
    bool m_removeFromChatList;

public:
    explicit QTdCloseSecretChatRequest(QObject *parent = nullptr);
    void setSecretChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QTDCLOSESECRETCHATREQUEST_H
