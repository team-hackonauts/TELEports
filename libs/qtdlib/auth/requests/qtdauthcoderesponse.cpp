#include "qtdauthcoderesponse.h"

QTdAuthCodeResponse::QTdAuthCodeResponse(QObject *parent)
    : QTdOkRequest(parent)
{
}

void QTdAuthCodeResponse::setCode(const QString &code)
{
    m_code = code;
}

QJsonObject QTdAuthCodeResponse::marshalJson()
{
    return QJsonObject{
        { "@type", "checkAuthenticationCode" },
        { "code", m_code },
    };
}
