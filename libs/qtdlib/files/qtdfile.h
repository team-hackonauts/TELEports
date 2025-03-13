#ifndef QTDFILE_H
#define QTDFILE_H

#include <QObject>
#include <QScopedPointer>
#include "common/qabstractint64id.h"
#include "qtdlocalfile.h"
#include "qtdremotefile.h"

class QTdFile : public QAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QString size READ qmlSize NOTIFY fileChanged)
    Q_PROPERTY(QString expectedSize READ qmlExpectedSize NOTIFY fileChanged)
    Q_PROPERTY(QTdLocalFile *local READ local NOTIFY fileChanged)
    Q_PROPERTY(QTdRemoteFile *remote READ remote NOTIFY fileChanged)
public:
    explicit QTdFile(QObject *parent = nullptr);

    qint32 size() const;
    QString qmlSize() const;

    qint32 expectedSize() const;
    QString qmlExpectedSize() const;

    QTdLocalFile *local() const;

    QTdRemoteFile *remote() const;

    void unmarshalJson(const QJsonObject &json) override;

    Q_INVOKABLE void downloadFile();

signals:
    void fileChanged();

private slots:
    void handleUpdateFile(const QJsonObject &json);

private:
    QTdInt53 m_size;
    QTdInt53 m_expectedSize;
    QScopedPointer<QTdLocalFile> m_local;
    QScopedPointer<QTdRemoteFile> m_remote;
};

#endif // QTDFILE_H
