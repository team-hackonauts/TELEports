#include "qtdconnectionmanager.h"
#include <QDebug>
#include <QtGui/QGuiApplication>
#include "client/qtdclient.h"

QTdConnectionManager::QTdConnectionManager(QObject *parent)
    : QObject(parent)
    , m_connectionState(WaitingForNetwork)
{
    connect(QTdClient::instance(),
            &QTdClient::connectionStateChanged,
            this,
            &QTdConnectionManager::handleConnectionStateChanged);

    // Manually run the update now as the client may already be initialized
    // so we want the *current* state to set us up correctly.
    if (QTdClient::instance()->connectionState()) {
        handleConnectionStateChanged(QTdClient::instance()->connectionState());
    }
    connect(qGuiApp, &QGuiApplication::applicationStateChanged, this,
            &QTdConnectionManager::handleApplicationStateChanged);
}

QTdConnectionManager::ConnectionState QTdConnectionManager::connectionState() const
{
    return m_connectionState;
}

bool QTdConnectionManager::connectivityOnline() const
{
    return m_connectivity_online;
}

void QTdConnectionManager::setConnectivityOnline(bool value)
{
#if defined(__amd64__)
    qDebug() << "ConnectivityOnline on amd64 as online";
    value = 1;
#endif
    if (m_connectivity_online != value) {
        m_connectivity_online = value;
        emit connectivityOnlineChanged(value);
        setTdLibNetworkState();
    }
}

void QTdConnectionManager::handleConnectionStateChanged(QTdConnectionState *state)
{
    if (!state)
        return;
    switch (state->type()) {
    case QTdConnectionState::Type::CONNECTION_STATE_WAITING_FOR_NETWORK: {
        m_connectionState = WaitingForNetwork;
        emit waitingForNetwork();
        break;
    }
    case QTdConnectionState::Type::CONNECTION_STATE_CONNECTING_TO_PROXY: {
        m_connectionState = ConnectingToProxy;
        emit connectingToProxy();
        break;
    }
    case QTdConnectionState::Type::CONNECTION_STATE_CONNECTING: {
        m_connectionState = Connecting;
        emit connecting();
        break;
    }
    case QTdConnectionState::Type::CONNECTION_STATE_UPDATING: {
        m_connectionState = Updating;
        emit updating();
        break;
    }
    case QTdConnectionState::Type::CONNECTION_STATE_READY: {
        m_connectionState = Ready;
        emit ready();
        break;
    }
    default:
        return;
    }
    emit connectionStateChanged(m_connectionState);
}

void QTdConnectionManager::handleApplicationStateChanged(Qt::ApplicationState state)
{
    auto application_suspended = state == Qt::ApplicationState::ApplicationSuspended;
    if (m_application_suspended != application_suspended) {
        m_application_suspended = application_suspended;
        setTdLibNetworkState();
    }
}

void QTdConnectionManager::setTdLibNetworkState()
{
    if (m_connectivity_online && !m_application_suspended) {
        QTdClient::instance()->send(QJsonObject{
                { "@type", "setNetworkType" },
                { "type", QJsonObject{ { "@type", "networkTypeMobile" } } } });
    } else {
        QTdClient::instance()->send(QJsonObject{
                { "@type", "setNetworkType" },
                { "type", QJsonObject{ { "@type", "networkTypeNone" } } } });
    }
}
