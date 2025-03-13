#include "qtdgetmessagelinkrequest.h"
#include "client/qtdclient.h"

QTdGetMessageLinkRequest::QTdGetMessageLinkRequest(QObject *parent)
    : QTdRequest(parent)
{
}

void QTdGetMessageLinkRequest::setChatId(const qint64 &chat)
{
    m_chat = chat;
}

void QTdGetMessageLinkRequest::setMessageId(const qint64 &msg)
{
    m_msg = msg;
}

void QTdGetMessageLinkRequest::setMediaTimestamp(const qint32 &timestamp)
{
    m_media_timestamp = timestamp;
}

void QTdGetMessageLinkRequest::setForAlbum(const bool &forAlbum)
{
    m_for_album = forAlbum;
}

void QTdGetMessageLinkRequest::setForComment(const bool &forComment)
{
    m_for_comment = forComment;
}

QJsonObject QTdGetMessageLinkRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getMessageLink" },
        { "chat_id", m_chat },
        { "message_id", m_msg },
        { "media_timestamp", m_media_timestamp },
        { "for_album", m_for_album },
        { "for_comment", m_for_comment }
    };
}

QFuture<QTdResponse> QTdGetMessageLinkRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::messageLink);
}
