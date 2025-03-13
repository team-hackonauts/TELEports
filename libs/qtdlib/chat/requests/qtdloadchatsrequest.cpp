#include "qtdloadchatsrequest.h"
#include "client/qtdclient.h"

QTdLoadChatsRequest::QTdLoadChatsRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatList(QStringLiteral("chatListMain"))
{
}

QJsonObject QTdLoadChatsRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "loadChats" },
        { "chat_list", QJsonObject { { "@type", m_chatList } } },
        { "limit", m_limit },
    };
}

void QTdLoadChatsRequest::setChatList(const QString chatList)
{
    m_chatList = chatList;
}

void QTdLoadChatsRequest::setLimit(const qint64 value)
{
    m_limit = value;
}

