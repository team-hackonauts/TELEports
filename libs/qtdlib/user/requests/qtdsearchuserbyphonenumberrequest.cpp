#include "qtdsearchuserbyphonenumberrequest.h"

#include "client/qtdclient.h"

QTdSearchUserByPhoneNumberRequest::QTdSearchUserByPhoneNumberRequest(QObject *parent)
    : QTdRequest(parent)
{
}

void QTdSearchUserByPhoneNumberRequest::setPhoneNumber(const QString &value)
{
    m_phoneNumber = value;
}

QJsonObject QTdSearchUserByPhoneNumberRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "searchUserByPhoneNumber" },
        { "phone_number", m_phoneNumber },
    };
}

QFuture<QTdResponse> QTdSearchUserByPhoneNumberRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::user);
}