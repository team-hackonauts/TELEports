#ifndef QTDREMOVEPROXYREQUEST_H
#define QTDREMOVEPROXYREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdGetProxiesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_proxies.html
 */
class QTdRemoveProxyRequest : public QTdOkRequest
{
    Q_OBJECT

public:
    explicit QTdRemoveProxyRequest(QObject *parent = nullptr);
    QJsonObject marshalJson();

    void setId(qint32 value);
    
private:
    qint32 m_id;
};

#endif // QTDREMOVEPROXYREQUEST_H