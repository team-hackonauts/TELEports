#include "qtdblockuserrequest.h"

QTdBlockUserRequest::QTdBlockUserRequest(QObject *parent)
    : QTdOkRequest(parent)
{
}

void QTdBlockUserRequest::setUser(QTdUser *user)
{
    m_userId = user->id();
}

void QTdBlockUserRequest::setUserId(const qint64 &id)
{
    m_userId = id;
}

void QTdBlockUserRequest::setUserId(const QString &id)
{
    m_userId = id.toLongLong();
}

QJsonObject QTdBlockUserRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "blockUser" },
        { "user_id", m_userId },
    };
}
