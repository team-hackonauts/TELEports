#ifndef QTDGETCHATHISTORYREQUEST_H
#define QTDGETCHATHISTORYREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdDeleteMessagesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1view_messages.html
 */
class QTdGetChatHistoryRequest : public QTdRequest
{
    Q_OBJECT
    qint64 m_chatId;
    qint64 m_fromMessageId;
    qint32 m_offset;
    qint32 m_limit;
    bool m_onlyLocal;

public:
    explicit QTdGetChatHistoryRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    void setFromMessageId(const qint64 &fromMessageId);
    void setOffset(const qint32 &offset);
    void setLimit(const qint32 &limit);
    void setOnlyLocal(bool value);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();
};

#endif // QTDGETCHATHISTORYREQUEST_H
