#ifndef QTDAUTHRESENDCODEREQUEST_H
#define QTDAUTHRESENDCODEREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdAuthRegistrationResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1register_user.html
 */
class QTdAuthResendCodeRequest : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdAuthResendCodeRequest)

public:
    explicit QTdAuthResendCodeRequest(QObject *parent = nullptr);

        /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

};
#endif // QTDAUTHRESENDCODEREQUEST_H