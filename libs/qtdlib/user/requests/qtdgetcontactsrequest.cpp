#include "qtdgetcontactsrequest.h"
#include "client/qtdclient.h"

QTdGetContactsRequest::QTdGetContactsRequest(QObject *parent)
    : QTdRequest(parent)
{
}

QJsonObject QTdGetContactsRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getContacts" }
    };
}

QFuture<QTdResponse> QTdGetContactsRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::users);
}
