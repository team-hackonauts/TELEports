#ifndef QTDEDITROXYREQUEST_H
#define QTDEDITROXYREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"
#include "../qtdproxytype.h"

/**
 * @brief The QTdAddProxyRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1add_proxy.html
 */
class QTdEditProxyRequest : public QTdRequest
{
    Q_OBJECT

public:
    explicit QTdEditProxyRequest(QObject *parent = nullptr);

    void setId(qint32 value);
    void setServer(QString value);
    void setPort(qint32 value);
    void setType(QPointer<QTdProxyType> value);
    void setEnable(bool value);

    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();

private:
qint32 m_id;
    QString m_server;
    qint32 m_port;
    bool m_enable;
    QPointer<QTdProxyType> m_type;
};

#endif // QTDEDITROXYREQUEST_H