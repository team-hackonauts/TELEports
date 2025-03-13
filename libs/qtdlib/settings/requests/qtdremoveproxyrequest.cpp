#include "qtdremoveproxyrequest.h"
#include "client/qtdclient.h"

QTdRemoveProxyRequest::QTdRemoveProxyRequest(QObject *parent)
    : QTdOkRequest(parent)
{
}

void QTdRemoveProxyRequest::setId(qint32 value)
{
    m_id = value;
}

QJsonObject QTdRemoveProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "removeProxy" },
        { "proxy_id", m_id }
    };
}
