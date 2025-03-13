#ifndef QTDVIEWMESSAGESREQUEST_H
#define QTDVIEWMESSAGESREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdViewMessagesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1view_messages.html
 */
class QTdViewMessagesRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    QList<qint64> m_messageIds;

public:
    explicit QTdViewMessagesRequest(QObject *parent = nullptr);
    void setMessageIds(const QList<qint64> &messageIds);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
};

#endif // QTDVIEWMESSAGESREQUEST_H
