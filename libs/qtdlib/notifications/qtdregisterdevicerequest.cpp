#include "qtdregisterdevicerequest.h"
#include "client/qtdclient.h"

QTdRegisterDeviceRequest::QTdRegisterDeviceRequest(QObject *parent)
    : QTdRequest(parent)
{
}

void QTdRegisterDeviceRequest::setToken(const QString &token)
{
    m_token = token;
}

QJsonObject QTdRegisterDeviceRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "registerDevice" },
        { "device_token", QJsonObject{
                                  { "@type", "deviceTokenUbuntuPush" },
                                  { "token", m_token } } }
    };
}

QFuture<QTdResponse> QTdRegisterDeviceRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::pushReceiverId);
}
