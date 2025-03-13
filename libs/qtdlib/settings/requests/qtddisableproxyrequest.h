#ifndef QTDDISABLEPROXYREQUEST_H
#define QTDDISABLEPROXYREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdGetProxiesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_proxies.html
 */
class QTdDisableProxyRequest : public QTdOkRequest
{
    Q_OBJECT

public:
    explicit QTdDisableProxyRequest(QObject *parent = nullptr);
    QJsonObject marshalJson();

};

#endif // QTDDISABLEPROXYREQUEST_H