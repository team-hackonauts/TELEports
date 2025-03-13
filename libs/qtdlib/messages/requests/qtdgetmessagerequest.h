#ifndef QTDGETMESSAGEREQUEST_H
#define QTDGETMESSAGEREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdGetMessageRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_message.html
 */
class QTdGetMessageRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdGetMessageRequest(QObject *parent = nullptr);

    void setChatId(const qint64 &chat);

    void setMessageId(const qint64 &msg);

    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();

private:
    qint64 m_chat{ 0 };
    qint64 m_msg{ 0 };
};

#endif // QTDGETMESSAGEREQUEST_H
