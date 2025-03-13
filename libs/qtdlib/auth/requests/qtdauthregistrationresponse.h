#ifndef QTDAUTHREGISTRATIONRESPONSE_H
#define QTDAUTHREGISTRATIONRESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdAuthRegistrationResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1register_user.html
 */
class QTdAuthRegistrationResponse : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdAuthRegistrationResponse)
public:
    explicit QTdAuthRegistrationResponse(QObject *parent = nullptr);

    /**
     * @brief setFirstName
     * @param firstname
     *
     * The first name of the user; 1-64 characters
     */
    void setFirstName(const QString &firstname);

    /**
     * @brief setLastName
     * @param lastname
     *
     * The last name of the user; 0-64 characters.
     */
    void setLastName(const QString &lastname);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_firstname;
    QString m_lastname;
};

#endif // QTDAUTHREGISTRATIONRESPONSE_H
