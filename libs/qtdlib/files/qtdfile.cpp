#include "qtdfile.h"
#include <QDebug>
#include <QScopedPointer>
#include "client/qtdclient.h"
#include "files/qtddownloadfilerequest.h"

QTdFile::QTdFile(QObject *parent)
    : QAbstractInt64Id(parent)
    , m_size(0)
    , m_expectedSize(0)
    , m_local(new QTdLocalFile)
    , m_remote(new QTdRemoteFile)
{
    setType(FILE);
    connect(QTdClient::instance(), &QTdClient::updateFile, this, &QTdFile::handleUpdateFile);
}

qint32 QTdFile::size() const
{
    return m_size.value();
}

QString QTdFile::qmlSize() const
{
    return m_size.toQmlValue();
}

qint32 QTdFile::expectedSize() const
{
    return m_expectedSize.value();
}

QString QTdFile::qmlExpectedSize() const
{
    return m_expectedSize.toQmlValue();
}

QTdLocalFile *QTdFile::local() const
{
    return m_local.data();
}

QTdRemoteFile *QTdFile::remote() const
{
    return m_remote.data();
}

void QTdFile::unmarshalJson(const QJsonObject &json)
{
    QAbstractInt64Id::unmarshalJson(json);
    m_local->unmarshalJson(json["local"].toObject());
    m_remote->unmarshalJson(json["remote"].toObject());
    m_size = json["size"];
    m_expectedSize = json["expected_size"];
    emit fileChanged();
}

void QTdFile::downloadFile()
{
    if (!m_local->canBeDownloaded()) {
        return;
    }
    QScopedPointer<QTdDownloadFileRequest> req(new QTdDownloadFileRequest);
    req->setFileId(this->id());
    req->setPriority(QTdDownloadFileRequest::Priority::Medium);
    QTdClient::instance()->send(req.data());
}

void QTdFile::handleUpdateFile(const QJsonObject &json)
{
    if (json["id"].toVariant().toLongLong() != this->id()) {
        return;
    }
    this->unmarshalJson(json);
}
