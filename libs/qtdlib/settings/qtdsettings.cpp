#include "qtdsettings.h"

#include <QJsonObject>
#include <QJsonArray>

#include "utils/await.h"
#include "client/qtdclient.h"
#include "qtdproxytype.h"
#include "requests/qtdgetproxiesrequest.h"
#include "requests/qtdaddproxyrequest.h"
#include "requests/qtdeditproxyrequest.h"
#include "requests/qtdremoveproxyrequest.h"
#include "requests/qtdenableproxyrequest.h"
#include "requests/qtddisableproxyrequest.h"

QTdSettings::QTdSettings(QObject *parent)
    : QTdObject(parent)
{
    m_proxies.reset(new QQmlObjectListModel<QTdProxy>(this, "", "id"));
    connect(QTdClient::instance(), &QTdClient::proxy, this, &QTdSettings::fetchProxyServers);
}

QObject *QTdSettings::qmlProxies() const
{
    return m_proxies.data();
}

QQmlObjectListModel<QTdProxy> *QTdSettings::proxies() const
{
    return m_proxies.data();
}

void QTdSettings::addOrEditProxyServer(qint32 id, QString server, qint32 port, qint32 type, QString username, QString password, QString secret, bool httpOnly, bool enable)
{
    QScopedPointer<QTdProxyType> typeObject;
    QTdProxyType *proxyType = Q_NULLPTR;
    switch(type) {
        case 0:
        {
            proxyType = new QTdProxyTypeHttp();
            proxyType->setUsername(username);
            proxyType->setPassword(password);
            proxyType->setHttpOnly(httpOnly);
            break;
        }
        case 1:
        {
            proxyType = new QTdProxyTypeMtproto();
            proxyType->setSecret(secret);
            break;
        }
        case 2:
        {
            proxyType = new QTdProxyTypeSocks5();
            proxyType->setUsername(username);
            proxyType->setPassword(password);
            break;
        }
    }
    typeObject.reset(proxyType);

    QFuture<QTdResponse> resp;
    if (id == -1) {
        QScopedPointer<QTdAddProxyRequest> req(new QTdAddProxyRequest());
        req->setServer(server);
        req->setPort(port);
        req->setType(typeObject.data());
        req->setEnable(enable);
        resp = req->sendAsync();
    } else {
        QScopedPointer<QTdEditProxyRequest> req(new QTdEditProxyRequest());
        req->setId(id);
        req->setServer(server);
        req->setPort(port);
        req->setType(typeObject.data());
        req->setEnable(enable);
        resp = req->sendAsync();
    }
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during adding/editing proxy:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
    }
}

void QTdSettings::deleteProxyServer(qint32 id)
{
    QScopedPointer<QTdRemoveProxyRequest> req(new QTdRemoveProxyRequest());
    req->setId(id);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during deleting proxy:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
        return;
    }
    auto proxy = (QTdProxy*) m_proxies->get(QString::number(id));
    m_proxies->remove(proxy);
    fetchProxyServers();
}

void QTdSettings::disableProxyServer()
{
    QScopedPointer<QTdDisableProxyRequest> req(new QTdDisableProxyRequest());
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during disabling proxy:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
        return;
    }
    fetchProxyServers();
}

void QTdSettings::enableProxyServer(qint32 id)
{
    QScopedPointer<QTdEnableProxyRequest> req(new QTdEnableProxyRequest());
    req->setId(id);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during enabling proxy:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
        return;
    }
    fetchProxyServers();
}

void QTdSettings::fetchProxyServers()
{
    QScopedPointer<QTdGetProxiesRequest> req(new QTdGetProxiesRequest);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during getting proxies:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
        return;
    }
    handleProxyServers(resp.result().json());

}

void QTdSettings::handleProxyServers(const QJsonObject &json)
{
    auto array = json["proxies"].toArray();
    for (auto value : array) {
        auto json = value.toObject();
        auto proxy = (QTdProxy*) m_proxies->get(QString::number(json["id"].toDouble()));
        if (!proxy) {
            proxy = new QTdProxy(this);
            connect(proxy, &QTdProxy::pingError, this, &QTdSettings::proxyPingError);
            m_proxies.data()->append(proxy);
        }       
        proxy->unmarshalJson(json);
    }
    emit proxiesChanged();
}

