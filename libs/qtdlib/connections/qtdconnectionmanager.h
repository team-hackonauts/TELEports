#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include "qtdconnectionstate.h"

class QTdConnectionManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConnectionState connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(bool connectivityOnline READ connectivityOnline WRITE setConnectivityOnline NOTIFY connectivityOnlineChanged)
public:
    explicit QTdConnectionManager(QObject *parent = nullptr);

    enum ConnectionState {
        WaitingForNetwork,
        ConnectingToProxy,
        Connecting,
        Updating,
        Ready
    };
    Q_ENUM(ConnectionState)
    ConnectionState connectionState() const;
    bool connectivityOnline() const;
    void setConnectivityOnline(bool value);

signals:
    void connectionStateChanged(ConnectionState state);
    void connectivityOnlineChanged(bool connectivityOnline);
    void waitingForNetwork();
    void connectingToProxy();
    void connecting();
    void updating();
    void ready();

private slots:
    void handleConnectionStateChanged(QTdConnectionState *state);
    void handleApplicationStateChanged(Qt::ApplicationState state);

private:
    void setTdLibNetworkState();
    ConnectionState m_connectionState;
    bool m_connectivity_online;
    bool m_application_suspended;
};

#endif // CONNECTIONMANAGER_H