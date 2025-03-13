#ifndef QTDSETTINGS_H
#define QTDSETTINGS_H

#include <QObject>
#include <QScopedPointer>
#include "common/qabstracttdobject.h"
#include "models/QmlObjectListModel.h"
#include "qtdproxy.h"

class QTdSettings : public QTdObject {

    Q_OBJECT
    Q_PROPERTY(QObject *proxies READ qmlProxies NOTIFY proxiesChanged)

public:
    explicit QTdSettings(QObject *parent = nullptr);

    QObject *qmlProxies() const;
    QQmlObjectListModel<QTdProxy> *proxies() const;

    Q_INVOKABLE void addOrEditProxyServer(qint32 id, QString server, qint32 port, qint32 type, QString username, QString password, QString secret, bool httpOnly, bool enable);
    Q_INVOKABLE void deleteProxyServer(qint32 id);
    Q_INVOKABLE void enableProxyServer(qint32 id);
    Q_INVOKABLE void disableProxyServer();
    Q_INVOKABLE void fetchProxyServers();

signals:
    void proxiesChanged();
    void proxyManagementError(QString errorMessage);
    void proxyPingError(int id, QString errorMessage);

private:
    void handleProxyServers(const QJsonObject &json);

    QScopedPointer<QQmlObjectListModel<QTdProxy>> m_proxies;
};

#endif // QTDSETTINGS_H