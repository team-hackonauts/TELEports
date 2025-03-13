#ifndef QTDAUTHPHONENUMBERRESPONSE_H
#define QTDAUTHPHONENUMBERRESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdAuthPhoneNumberResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_authentication_phone_number.html
 */
class QTdAuthPhoneNumberResponse : public QTdOkRequest
{
    Q_OBJECT
public:
    explicit QTdAuthPhoneNumberResponse(QObject *parent = nullptr);

    void setPhoneNumber(const QString &number);

    QJsonObject marshalJson();

private:
    QString m_number;
};

#endif // QTDAUTHPHONENUMBERRESPONSE_H
