#ifndef QTDTHUMBNAIL_H
#define QTDTHUMBNAIL_H

#include <QObject>
#include <QScopedPointer>
#include "common/qabstracttdobject.h"
#include "qtdfile.h"
#include "qtdthumbnailformat.h"

class QTdThumbnail : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QTdThumbnailFormat *format READ format NOTIFY thumbnailChanged)
    Q_PROPERTY(QTdFile *file READ file NOTIFY thumbnailChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY thumbnailChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY thumbnailChanged)
public:
    explicit QTdThumbnail(QObject *parent = nullptr);

    QTdThumbnailFormat *format() const;

    QTdFile *file() const;

    qint32 width() const;

    qint32 height() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void thumbnailChanged();

private:
    QScopedPointer<QTdThumbnailFormat> m_format;
    QScopedPointer<QTdFile> m_file;
    qint32 m_width;
    qint32 m_height;
};

#endif // QTDTHUMBNAIL_H
