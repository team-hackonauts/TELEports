#include "qtdgetproxiesrequest.h"
#include "client/qtdclient.h"

QTdGetProxiesRequest::QTdGetProxiesRequest(QObject *parent)
    : QTdRequest(parent)
{
}

QJsonObject QTdGetProxiesRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getProxies" }
    };
}

QFuture<QTdResponse> QTdGetProxiesRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::proxies);
}