#include "qtdrequest.h"
#include <QDebug>
#include "client/qtdclient.h"

QTdRequest::QTdRequest(QObject *parent)
    : QTdObject(parent)
{
}

void QTdRequest::send()
{
    return QTdClient::instance()->send(this);
}

QFuture<QJsonObject> QTdRequest::exec()
{
    return QTdClient::instance()->exec(this);
}

QTdOkRequest::QTdOkRequest(QObject *parent)
    : QTdRequest(parent)
{
}

QFuture<QTdResponse> QTdOkRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::ok);
}
