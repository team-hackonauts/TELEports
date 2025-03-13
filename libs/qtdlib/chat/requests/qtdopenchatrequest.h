#ifndef QTDOPENCHATREQUEST_H
#define QTDOPENCHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdOpenChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1open_chat.html
 */
class QTdOpenChatRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;

public:
    explicit QTdOpenChatRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QTDOPENCHATREQUEST_H
