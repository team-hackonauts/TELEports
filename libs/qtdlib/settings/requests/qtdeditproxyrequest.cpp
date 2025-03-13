#include "qtdaddproxyrequest.h"
#include "client/qtdclient.h"
#include "qtdeditproxyrequest.h"

QTdEditProxyRequest::QTdEditProxyRequest(QObject *parent)
    : QTdRequest(parent)
{
}

QJsonObject QTdEditProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "editProxy" },
        { "proxy_id", m_id },
        { "server", m_server },
        { "port", m_port },
        { "enable", m_enable },
        { "type", m_type->marshalJson() }
    };
}

void QTdEditProxyRequest::setId(qint32 value)
{
    m_id = value;
}

void QTdEditProxyRequest::setServer(QString value)
{
    m_server = value;
}

void QTdEditProxyRequest::setPort(qint32 value) {
    m_port = value;
}

void QTdEditProxyRequest::setEnable(bool value) {
    m_enable = value;
}

void QTdEditProxyRequest::setType(QPointer<QTdProxyType> value) {
    m_type = value;
}

QFuture<QTdResponse> QTdEditProxyRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::proxy);
}