#ifndef QTDDELETEMESSAGESREQUEST_H
#define QTDDELETEMESSAGESREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdDeleteMessagesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1view_messages.html
 */
class QTdDeleteMessagesRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    QList<qint64> m_messageIds;
    bool m_revoke;

public:
    explicit QTdDeleteMessagesRequest(QObject *parent = nullptr);
    void setMessageIds(const QList<qint64> &messageIds);
    void setChatId(const qint64 &id);
    void setRevoke(bool value);
    QJsonObject marshalJson();
};

#endif // QTDVIEWMESSAGESREQUEST_H
