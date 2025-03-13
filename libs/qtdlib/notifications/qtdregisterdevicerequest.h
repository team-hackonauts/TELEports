#ifndef QTDREGISTERDEVICEREQUEST_H
#define QTDREGISTERDEVICEREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdRegisterDeviceRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1register_device.html
 */
class QTdRegisterDeviceRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdRegisterDeviceRequest(QObject *parent = nullptr);

    void setToken(const QString &token);

    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();

private:
    QString m_token;
};

#endif // QTDREGISTERDEVICEREQUEST_H
