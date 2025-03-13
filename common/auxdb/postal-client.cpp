/*
Copyright 2014 Canonical Ltd.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License, version 3
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this program.  If not, see
<http://www.gnu.org/licenses/>.
*/

#include "postal-client.h"
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusPendingCall>
#include <QtDBus/QDBusPendingReply>
#include <QTimer>

#define POSTAL_SERVICE "com.lomiri.Postal"
#define POSTAL_PATH "/com/lomiri/Postal"
#define POSTAL_IFACE "com.lomiri.Postal"

PostalClient::PostalClient(QString appId)
{
    this->m_appId = appId;
    this->m_pkgName = appId.split("_").at(0);
    this->m_pkgName = m_pkgName.replace(".", "_2e").replace("-", "_2d");
}

void PostalClient::clearPersistent(const QStringList &tags)
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    QString path(POSTAL_PATH);
    path += "/" + m_pkgName;
    QDBusMessage message = QDBusMessage::createMethodCall(
            POSTAL_SERVICE, path, POSTAL_IFACE, "ClearPersistent"); // no-i18n
    message << m_appId;
    for (int i = 0; i < tags.size(); ++i) {
        message << tags.at(i);
    }
    bus.send(message);

    QDBusPendingCall pcall = bus.asyncCall(message);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pcall, this);
    connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher *)),
            this, SLOT(clearPersistentFinished(QDBusPendingCallWatcher *)));
}

void PostalClient::clearPersistentFinished(QDBusPendingCallWatcher *watcher)
{
    QDBusPendingReply<void> reply = *watcher;

    if (reply.isError()) {
        //qWarning() << reply.error().message();
    }
    watcher->deleteLater();
}

void PostalClient::setCount(int count)
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    QString path(POSTAL_PATH);
    bool visible = count != 0;
    path += "/" + m_pkgName;
    QDBusMessage message = QDBusMessage::createMethodCall(POSTAL_SERVICE, path, POSTAL_IFACE, "SetCounter"); // no-i18n
    message << m_appId << count << visible;
    QDBusPendingCall pcall = bus.asyncCall(message);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pcall, this);
    connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher *)),
            this, SLOT(setCountFinished(QDBusPendingCallWatcher *)));
}

void PostalClient::setCountFinished(QDBusPendingCallWatcher *watcher)
{
    QDBusPendingReply<void> reply = *watcher;
    if (reply.isError()) {
        //qWarning() << reply.error().message();
    }
    watcher->deleteLater();
}
