#ifndef QTDCREATEPRIVATECHATREQUEST_H
#define QTDCREATEPRIVATECHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdCloseChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close_chat.html
 */
class QTdCreatePrivateChatRequest : public QTdRequest
{
    Q_OBJECT
    qint64 m_userId;
    bool m_force;

public:
    explicit QTdCreatePrivateChatRequest(QObject *parent = nullptr);

    /**
     * @brief setChatId
     * @param id of chat to close
     */
    void setUserId(const qint64 &id);
    void setForce(const bool &force);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();
};

#endif // QTDCREATEPRIVATECHATREQUEST_H
