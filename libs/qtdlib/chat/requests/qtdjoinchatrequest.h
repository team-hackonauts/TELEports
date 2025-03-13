#ifndef QTDJOINCHATREQUEST_H
#define QTDJOINCHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"
#include "common/qtdint.h"

/**
 * @brief The QTdJoinChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1join_chat.html
 */
class QTdJoinChatRequest : public QTdOkRequest
{
    Q_OBJECT
public:
    explicit QTdJoinChatRequest(QObject *parent = nullptr);

    void setChatId(const QString &chatId);
    void setChatId(const qint64 &chatId);
    QJsonObject marshalJson();

private:
    QTdInt64 m_chatId;
};

#endif // QTDJOINCHATREQUEST_H
