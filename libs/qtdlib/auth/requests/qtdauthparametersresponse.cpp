#include "qtdauthparametersresponse.h"

QTdAuthParametersResponse::QTdAuthParametersResponse(QObject *parent)
    : QTdOkRequest(parent)
{
}

void QTdAuthParametersResponse::setParameters(QTdAuthParams *params)
{
    m_params = params->marshalJson();
}

QJsonObject QTdAuthParametersResponse::marshalJson()
{
    auto result = m_params;
    result.insert("@type", "setTdlibParameters");
    return result;
}
