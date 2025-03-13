#ifndef QTDAUTHPASSWORDRESPONSE_H
#define QTDAUTHPASSWORDRESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdAuthPasswordResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1check_authentication_password.html
 */
class QTdAuthPasswordResponse : public QTdOkRequest
{
    Q_OBJECT
public:
    explicit QTdAuthPasswordResponse(QObject *parent = nullptr);

    /**
     * @brief setPassword
     * @param password to check
     */
    void setPassword(const QString &password);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_password;
};

#endif // QTDAUTHPASSWORDRESPONSE_H
