#include "qtdauthdeleteaccountresponse.h"

QTdAuthDeleteAccountResponse::QTdAuthDeleteAccountResponse(QObject *parent)
    : QTdOkRequest(parent)
{
}

void QTdAuthDeleteAccountResponse::setReason(const QString &reason)
{
    m_reason = reason;
}

QJsonObject QTdAuthDeleteAccountResponse::marshalJson()
{
    return QJsonObject{
        { "@type", "deleteAccount" },
        { "reason", m_reason },
    };
}
