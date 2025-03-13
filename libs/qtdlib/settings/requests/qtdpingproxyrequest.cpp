#include "qtdpingproxyrequest.h"
#include "client/qtdclient.h"

QTdPingProxyRequest::QTdPingProxyRequest(QObject *parent)
    : QTdRequest(parent)
{
}

void QTdPingProxyRequest::setId(qint32 value)
{
    m_id = value;
}

QJsonObject QTdPingProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "pingProxy" },
        { "proxy_id", m_id }
    };
}

QFuture<QTdResponse> QTdPingProxyRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::seconds);
}

