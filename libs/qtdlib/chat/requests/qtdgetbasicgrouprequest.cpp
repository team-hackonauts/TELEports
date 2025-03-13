#include "qtdgetbasicgrouprequest.h"
#include "client/qtdclient.h"

QTdGetBasicGroupRequest::QTdGetBasicGroupRequest(QObject *parent)
    : QTdRequest(parent)
    , m_groupId(0)
{
}

void QTdGetBasicGroupRequest::setGroupId(const qint64 groupId)
{
    m_groupId = groupId;
}

QJsonObject QTdGetBasicGroupRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "getBasicGroup" },
        { "basic_group_id", m_groupId },
    };
}

QFuture<QTdResponse> QTdGetBasicGroupRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::basicGroup);
}
