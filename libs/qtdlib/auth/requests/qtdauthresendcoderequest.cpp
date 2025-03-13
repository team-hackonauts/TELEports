#include "qtdauthresendcoderequest.h"

QTdAuthResendCodeRequest::QTdAuthResendCodeRequest(QObject *parent)
    : QTdOkRequest(parent)
{
}

QJsonObject QTdAuthResendCodeRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "resendPhoneNumberConfirmationCode" }
    };
}