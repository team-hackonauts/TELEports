#ifndef QTDAUTHCODERESPONSE_H
#define QTDAUTHCODERESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdAuthCodeResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1check_authentication_code.html
 */
class QTdAuthCodeResponse : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdAuthCodeResponse)
public:
    explicit QTdAuthCodeResponse(QObject *parent = nullptr);

    /**
     * @brief setCode
     * @param code
     *
     * The verification code received via SMS, Telegram or call
     */
    void setCode(const QString &code);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_code;
};

#endif // QTDAUTHCODERESPONSE_H
