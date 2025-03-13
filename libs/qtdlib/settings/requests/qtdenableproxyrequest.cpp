#include "qtdenableproxyrequest.h"
#include "client/qtdclient.h"

QTdEnableProxyRequest::QTdEnableProxyRequest(QObject *parent)
    : QTdOkRequest(parent)
{
}

void QTdEnableProxyRequest::setId(qint32 value)
{
    m_id = value;
}

QJsonObject QTdEnableProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "enableProxy" },
        { "proxy_id", m_id }
    };
}
