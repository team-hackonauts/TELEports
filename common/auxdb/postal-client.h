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

#ifndef POSTAL_CLIENT_H
#define POSTAL_CLIENT_H

#include <QObject>
#include <QString>

class QDBusPendingCallWatcher;

class PostalClient : public QObject
{
    Q_OBJECT

public:
    PostalClient(QString appId);

    void clearPersistent(const QStringList &tags);
    void setCount(int count);

private slots:
    void setCountFinished(QDBusPendingCallWatcher *watcher);
    void clearPersistentFinished(QDBusPendingCallWatcher *watcher);

private:
    QString m_appId;
    QString m_pkgName;
};
#endif // POSTAL_CLIENT.H