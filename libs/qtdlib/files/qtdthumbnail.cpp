#include "qtdthumbnail.h"

QTdThumbnail::QTdThumbnail(QObject *parent)
    : QTdObject(parent)
    , m_format(nullptr)
    , m_file(new QTdFile)
    , m_width(0)
    , m_height(0)
{
    setType(PHOTO_SIZE);
}

QTdThumbnailFormat *QTdThumbnail::format() const
{
    return m_format.data();
}

QTdFile *QTdThumbnail::file() const
{
    return m_file.data();
}

qint32 QTdThumbnail::width() const
{
    return m_width;
}

qint32 QTdThumbnail::height() const
{
    return m_height;
}

void QTdThumbnail::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    const QJsonObject format = json["format"].toObject();
    m_format.reset(QTdThumbnailFormat::create(format, this));
    m_file->unmarshalJson(json["file"].toObject());
    if (m_file->local()->path().isEmpty()) {
        m_file->downloadFile();
    }
    m_width = qint32(json["width"].toInt());
    m_height = qint32(json["height"].toInt());
    emit thumbnailChanged();
}
