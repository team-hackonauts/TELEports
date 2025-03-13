#include "qtdsearchpublicchatrequest.h"
#include "client/qtdclient.h"

QTdSearchPublicChatRequest::QTdSearchPublicChatRequest(QObject *parent)
    : QTdRequest(parent)
    , m_username("")
{
}

void QTdSearchPublicChatRequest::setChatUsername(const QString &username)
{
    m_username = username;
}

QJsonObject QTdSearchPublicChatRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "searchPublicChat" },
        { "username", m_username }
    };
}

QFuture<QTdResponse> QTdSearchPublicChatRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::chat);
}
