#ifndef QTDVIDEO_H
#define QTDVIDEO_H

#include <QObject>
#include <QScopedPointer>
#include "common/qabstracttdobject.h"
#include "common/qtdint.h"
#include "qtdthumbnail.h"
#include "qtdfile.h"

class QTdVideo : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 duration READ duration NOTIFY videoChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY videoChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY videoChanged)
    Q_PROPERTY(QString fileName READ fileName NOTIFY videoChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY videoChanged)
    Q_PROPERTY(QTdThumbnail *thumbnail READ thumbnail NOTIFY videoChanged)
    Q_PROPERTY(QTdFile *video READ video NOTIFY videoChanged)
public:
    explicit QTdVideo(QObject *parent = nullptr);

    qint32 duration() const;

    qint32 width() const;

    qint32 height() const;

    QString fileName() const;

    QString mimeType() const;

    QTdThumbnail *thumbnail() const;

    QTdFile *video() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void videoChanged();

private:
    qint32 m_duration;
    qint32 m_width;
    qint32 m_height;
    QString m_fileName;
    QString m_mimeType;
    QScopedPointer<QTdThumbnail> m_thumbnail;
    QScopedPointer<QTdFile> m_video;
};

#endif // QTDVIDEO_H
