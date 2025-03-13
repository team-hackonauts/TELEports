#ifndef QTDLEAVECHATREQUEST_H
#define QTDLEAVECHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdLeaveChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1leave_chat.html
 */
class QTdLeaveChatRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;

public:
    explicit QTdLeaveChatRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QTDLEAVECHATREQUEST_H
