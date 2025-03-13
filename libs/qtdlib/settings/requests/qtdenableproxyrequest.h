#ifndef QTDENABLEPROXYREQUEST_H
#define QTDENABLEPROXYREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdGetProxiesRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_proxies.html
 */
class QTdEnableProxyRequest : public QTdOkRequest
{
    Q_OBJECT

public:
    explicit QTdEnableProxyRequest(QObject *parent = nullptr);
    QJsonObject marshalJson();

    void setId(qint32 value);

private:
    qint32 m_id;
};

#endif // QTDENABLEPROXYREQUEST_H