#include "qtdauthregistrationresponse.h"

QTdAuthRegistrationResponse::QTdAuthRegistrationResponse(QObject *parent)
    : QTdOkRequest(parent)
{
}

void QTdAuthRegistrationResponse::setFirstName(const QString &firstname)
{
    m_firstname = firstname;
}

void QTdAuthRegistrationResponse::setLastName(const QString &lastname)
{
    m_lastname = lastname;
}

QJsonObject QTdAuthRegistrationResponse::marshalJson()
{
    return QJsonObject {
        { "@type", "registerUser" },
        { "first_name", m_firstname },
        { "last_name", m_lastname },
    };
}
