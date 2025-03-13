#ifndef QTDPINGPROXYREQUEST_H
#define QTDPINGPROXYREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdGetProxiesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1ping_proxy.html
 */
class QTdPingProxyRequest : public QTdRequest
{
    Q_OBJECT

public:
    explicit QTdPingProxyRequest(QObject *parent = nullptr);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();
    
    void setId(qint32 value);
    
private:
    qint32 m_id;
};

#endif // QTDPINGPROXYREQUEST_H