#include "qtdgetuserfullinforequest.h"
#include "client/qtdclient.h"

QTdGetUserFullInfoRequest::QTdGetUserFullInfoRequest(QObject *parent)
    : QTdRequest(parent)
{
}

void QTdGetUserFullInfoRequest::setUserId(const QString &id)
{
    setUserId(id.toLongLong());
}

void QTdGetUserFullInfoRequest::setUserId(const qint64 &id)
{
    m_uid = id;
}

QJsonObject QTdGetUserFullInfoRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getUserFullInfo" },
        { "user_id", m_uid.value() }
    };
}

QFuture<QTdResponse> QTdGetUserFullInfoRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::userFullInfo);
}
