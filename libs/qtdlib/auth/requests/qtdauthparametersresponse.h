#ifndef QTDAUTHPARAMETERSRESPONSE_H
#define QTDAUTHPARAMETERSRESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"
#include "auth/qtdauthparams.h"

/**
 * @brief The QTdAuthParametersResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_tdlib_parameters.html
 */
class QTdAuthParametersResponse : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdAuthParametersResponse)
public:
    explicit QTdAuthParametersResponse(QObject *parent = nullptr);

    /**
     * @brief setParameters
     * @param params - Parameters
     */
    void setParameters(QTdAuthParams *params);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QJsonObject m_params;
};

#endif // QTDAUTHPARAMETERSRESPONSE_H
