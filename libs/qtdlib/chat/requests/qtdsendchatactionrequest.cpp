#include "qtdsendchatactionrequest.h"

QTdSendChatActionRequest::QTdSendChatActionRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
{
}

void QTdSendChatActionRequest::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdSendChatActionRequest::setAction(const QTdChatAction &id)
{
}

QJsonObject QTdSendChatActionRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "sendChatAction" },
        { "chat_id", m_chatId },
        {
                "action", QJsonObject{
                                  { "@type", "chatActionTyping" },
                          },
        }
    };
}
