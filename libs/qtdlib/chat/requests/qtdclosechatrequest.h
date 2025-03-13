#ifndef QTDCLOSECHATREQUEST_H
#define QTDCLOSECHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdCloseChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close_chat.html
 */
class QTdCloseChatRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;

public:
    explicit QTdCloseChatRequest(QObject *parent = nullptr);

    /**
     * @brief setChatId
     * @param id of chat to close
     */
    void setChatId(const qint64 &id);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();
};

#endif // QTDCLOSECHATREQUEST_H
