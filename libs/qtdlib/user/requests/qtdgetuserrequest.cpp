#include "qtdgetuserrequest.h"
#include "client/qtdclient.h"

QTdGetUserRequest::QTdGetUserRequest(QObject *parent)
    : QTdRequest(parent)
{
}

void QTdGetUserRequest::setUserId(const QString &id)
{
    setUserId(id.toLongLong());
}

void QTdGetUserRequest::setUserId(const qint64 &id)
{
    m_uid = id;
}

QJsonObject QTdGetUserRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getUser" },
        { "user_id", m_uid.value() }
    };
}

QFuture<QTdResponse> QTdGetUserRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::user);
}
