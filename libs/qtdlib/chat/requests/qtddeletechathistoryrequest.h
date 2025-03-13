#ifndef QTDDELETECHATHISTORYREQUEST_H
#define QTDDELETECHATHISTORYREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdDeleteChatHistoryRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1delete_chat_history.html
 */
class QTdDeleteChatHistoryRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    bool m_removeFromChatList;
    bool m_revoke;

public:
    explicit QTdDeleteChatHistoryRequest(QObject *parent = nullptr);
    void setChatId(const qint64 &id);
    void setRemoveFromChatList(const bool &remove);
    void setRevoke(const bool &value);
    QJsonObject marshalJson();
};

#endif // QTDDELETECHATHISTORYREQUEST_H
