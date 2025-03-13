#include "qtdgetchatsrequest.h"
#include "client/qtdclient.h"

QTdGetChatsRequest::QTdGetChatsRequest(QObject *parent)
    : QTdRequest(parent)
    , m_chatList(QStringLiteral("chatListMain"))
{
}

QJsonObject QTdGetChatsRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "getChats" },
        { "chat_list", QJsonObject { { "@type", m_chatList } } },
        { "limit", m_limit },
    };
}

void QTdGetChatsRequest::setChatList(const QString chatList)
{
    m_chatList = chatList;
}

void QTdGetChatsRequest::setLimit(const qint64 value)
{
    m_limit = value;
}

QFuture<QTdResponse> QTdGetChatsRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::chats);
}
