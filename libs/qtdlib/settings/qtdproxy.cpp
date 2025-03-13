#include "qtdproxy.h"

#include "utils/asyncfuture.h"
#include "requests/qtdpingproxyrequest.h"

QTdProxy::QTdProxy(QObject *parent)
    : QAbstractInt64Id(parent)
{

}

QString QTdProxy::server() {
    return m_server;
}

qint32 QTdProxy::port() {
    return m_port;
}

qint32 QTdProxy::lastUsedDate() {
    return m_lastUsedDate;
}

bool QTdProxy::isEnabled() {
    return m_isEnabled;
}

QTdProxyType *QTdProxy::type() {
    return m_type.data();
}

double QTdProxy::ping()
{
    return m_ping;
}

void QTdProxy::setPing(double value)
{
    if (m_ping != value) {
        m_ping = value;
        emit pingChanged();
    }
}

void QTdProxy::unmarshalJson(const QJsonObject &json)
{
    QAbstractInt64Id::unmarshalJson(json);
    m_server = json["server"].toString();
    m_port = (int)json["port"].toDouble();
    m_lastUsedDate = (int)json["last_used_date"].toDouble();
    m_isEnabled = json["is_enabled"].toBool();
    m_type.reset(QTdProxyType::create(json["type"].toObject(), this));
    requestProxyServerPing();
    emit dataChanged();
}


void QTdProxy::requestProxyServerPing() {
    m_ping = -1;
    QScopedPointer<QTdPingProxyRequest> req(new QTdPingProxyRequest);
    req->setId(id());
    auto future = req->sendAsync();
    AsyncFuture::observe(future).subscribe([this](QTdResponse resp) {
        if (resp.isError()) {
            auto errorMessage = resp.errorString();
            qWarning() << "Error during pinging proxy:" << errorMessage;
            emit pingError(id(), errorMessage);
            return;
        }
        setPing(resp.json()["seconds"].toDouble() * 1000);
        emit pingError(id(), "");
    });

    
}

