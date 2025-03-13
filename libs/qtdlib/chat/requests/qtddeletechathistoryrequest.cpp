#include "qtddeletechathistoryrequest.h"

QTdDeleteChatHistoryRequest::QTdDeleteChatHistoryRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
    , m_removeFromChatList(false)
{
}

void QTdDeleteChatHistoryRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdDeleteChatHistoryRequest::setRemoveFromChatList(const bool &remove)
{
    m_removeFromChatList = remove;
}

void QTdDeleteChatHistoryRequest::setRevoke(const bool &value)
{
    m_revoke = value;
}

QJsonObject QTdDeleteChatHistoryRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "deleteChatHistory" },
        { "chat_id", m_chatId },
        { "remove_from_chat_list", m_removeFromChatList },
        { "revoke", m_revoke }
    };
}
