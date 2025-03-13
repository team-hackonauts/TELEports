#include "qtdgetsupergrouprequest.h"
#include "client/qtdclient.h"

QTdGetSuperGroupRequest::QTdGetSuperGroupRequest(QObject *parent)
    : QTdRequest(parent)
    , m_sgId(0)
{
}

void QTdGetSuperGroupRequest::setSuperGroupId(const qint64 &id)
{
    m_sgId = id;
}

QJsonObject QTdGetSuperGroupRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getSupergroup" },
        { "supergroup_id", m_sgId },
    };
}

QFuture<QTdResponse> QTdGetSuperGroupRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::superGroup);
}
