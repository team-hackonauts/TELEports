#include "qtdaddproxyrequest.h"
#include "client/qtdclient.h"

QTdAddProxyRequest::QTdAddProxyRequest(QObject *parent)
    : QTdRequest(parent)
{
}

QJsonObject QTdAddProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "addProxy" },
        { "server", m_server },
        { "port", m_port },
        { "enable", m_enable },
        { "type", m_type->marshalJson() }
    };
}

void QTdAddProxyRequest::setServer(QString value) {
    m_server = value;
}

void QTdAddProxyRequest::setPort(qint32 value) {
    m_port = value;
}

void QTdAddProxyRequest::setEnable(bool value) {
    m_enable = value;
}

void QTdAddProxyRequest::setType(QPointer<QTdProxyType> value) {
    m_type = value;
}

QFuture<QTdResponse> QTdAddProxyRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::proxy);
}