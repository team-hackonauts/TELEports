#include "qtdenablenotifications.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QThread>
#include "client/qtdclient.h"
#include "qtdregisterdevicerequest.h"

#define PUSHTOKEN_REREGISTER_TIME 14400

QTdEnableNotifications::QTdEnableNotifications(QObject *parent)
    : QObject(parent),
    m_registrationThread(Q_NULLPTR)
{
    connect(QTdClient::instance(), &QTdClient::authStateChanged, [=](QTdAuthState *state) {
        if (!m_token.isEmpty() && state->type() == QTdAuthState::Type::AUTHORIZATION_STATE_READY) {
            registerDevice();
        }
    });

    connect(&m_watcher, &QFutureWatcher<QTdResponse>::finished, this, &QTdEnableNotifications::handleResponse);
}

QString QTdEnableNotifications::token() const
{
    return m_token;
}

void QTdEnableNotifications::setToken(const QString &token)
{
    if (token != m_token) {
        m_token = token;
    }
    emit tokenChanged();

    // Only register the device if we are authenticated and state is ready
    // We don't want to be sending this early as it could be sent before an account
    // is even configured (first time setup) and then it would require an app restart
    // to get this to send again. If it isn't sent now the authStateChanged connection
    // will register the device once ready.
    if (!m_token.isEmpty() && QTdClient::instance()->authState()->type() == QTdAuthState::Type::AUTHORIZATION_STATE_READY) {
        return registerDevice();
    }
    qDebug() << "Delaying registering device for push notification until account is authenticated";
}

void QTdEnableNotifications::registerDevice()
{
    if (m_token.isEmpty()) {
        qWarning() << "Cannot register device. No push token set";
        return;
    }
    threadLocker.lock();
    if (m_registrationThread) {
        qWarning() << "push notification registration thread already running!";
        return;
    }
    m_registrationThread.reset(QThread::create([this]{
    QScopedPointer<QTdRegisterDeviceRequest> req(new QTdRegisterDeviceRequest);
    req->setToken(m_token);
        while(true) {
            qDebug() << "Registering device for push notifications";
            m_watcher.setFuture(req->sendAsync());
            QThread::sleep(PUSHTOKEN_REREGISTER_TIME);
        }
    }));
    m_registrationThread->start();
    threadLocker.unlock();
}

void QTdEnableNotifications::handleResponse()
{
    const QTdResponse resp = m_watcher.result();
    if (resp.isOk()) {
        qDebug() << "Push notifications enabled";
        emit enabled();
        return;
    }
    if (resp.isError()) {
        emit error(resp.errorString());
    }
}

QTdEnableNotifications::~QTdEnableNotifications() {
    m_registrationThread->terminate();
}
