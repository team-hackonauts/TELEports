#include "qtdremovecontactsrequest.h"

QTdRemoveContactsRequest::QTdRemoveContactsRequest(QObject *parent)
    : QTdOkRequest(parent)
{
}

void QTdRemoveContactsRequest::setUserIds(const QList<qint64> &userIds)
{
    m_userIds = userIds;
}

QJsonObject QTdRemoveContactsRequest::marshalJson()
{
    QJsonArray json_userids;
    for (auto &m_userId : m_userIds)
        json_userids.append(m_userId);
    return QJsonObject{
        { "@type", "removeContacts" },
        { "user_ids", json_userids }
    };
}
