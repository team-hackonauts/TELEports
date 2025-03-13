#include "qtddisableproxyrequest.h"
#include "client/qtdclient.h"

QTdDisableProxyRequest::QTdDisableProxyRequest(QObject *parent)
    : QTdOkRequest(parent)
{
}

QJsonObject QTdDisableProxyRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "disableProxy" }
    };
}
