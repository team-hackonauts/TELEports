#ifndef QTDGETCHATREQUEST_H
#define QTDGETCHATREQUEST_H

#include <QObject>
#include <QtConcurrent>
#include "common/qtdrequest.h"
#include "common/qtdresponse.h"

/**
 * @brief The QTdGetChatsRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_chat.html
 */
class QTdGetChatRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdGetChatRequest(QObject *parent = nullptr);

    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();

    void setChatId(const QString &id);

    void setChatId(const qint64 &id);

private:
    qint64 m_chat_id;
};

#endif // QTDGETCHATREQUEST_H
