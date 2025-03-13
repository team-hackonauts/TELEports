#ifndef QTDPROXY_H
#define QTDPROXY_H

#include <QObject>
#include <QScopedPointer>
#include "common/qabstractint64id.h"
#include "qtdproxytype.h"

class QTdProxy : public QAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QString server READ server NOTIFY dataChanged)
    Q_PROPERTY(qint32 port READ port NOTIFY dataChanged)
    Q_PROPERTY(qint32 lastUsedDate READ lastUsedDate NOTIFY dataChanged)
    Q_PROPERTY(bool isEnabled READ isEnabled NOTIFY dataChanged)
    Q_PROPERTY(QTdProxyType *type READ type NOTIFY dataChanged)
    Q_PROPERTY(double ping READ ping NOTIFY pingChanged)

public:
    explicit QTdProxy(QObject *parent = nullptr);
    void unmarshalJson(const QJsonObject &json) override;

    QString server();
    qint32 port();
    qint32 lastUsedDate();
    bool isEnabled();
    QTdProxyType *type();
    double ping();
    void setPing(double value);
    
signals:
    void dataChanged();
    void pingChanged();
    void pingError(int id, QString errorMessage);

private:
    void requestProxyServerPing();
    QString m_server;
    qint32 m_port;
    qint32 m_lastUsedDate;
    bool m_isEnabled;
    QScopedPointer<QTdProxyType> m_type;
    double m_ping;
};

#endif // QTDPROXY_H