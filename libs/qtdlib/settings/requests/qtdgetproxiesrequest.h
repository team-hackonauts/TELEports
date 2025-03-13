#ifndef QTDGETPROXIESREQUEST_H
#define QTDGETPROXIESREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdGetProxiesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_proxies.html
 */
class QTdGetProxiesRequest : public QTdRequest
{
    Q_OBJECT

public:
    explicit QTdGetProxiesRequest(QObject *parent = nullptr);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();
};

#endif // QTDGETPROXIESREQUEST_H