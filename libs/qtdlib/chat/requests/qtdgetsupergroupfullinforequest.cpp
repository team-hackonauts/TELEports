#include "qtdgetsupergroupfullinforequest.h"
#include "client/qtdclient.h"

QTdGetSuperGroupFullInfoRequest::QTdGetSuperGroupFullInfoRequest(QObject *parent)
    : QTdRequest(parent)
    , m_id(0)
{
}

void QTdGetSuperGroupFullInfoRequest::setSupergroupId(const qint64 &id)
{
    m_id = id;
}

QJsonObject QTdGetSuperGroupFullInfoRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getSupergroupFullInfo" },
        { "supergroup_id", m_id }
    };
}

QFuture<QTdResponse> QTdGetSuperGroupFullInfoRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::supergroupFullInfo);
}
