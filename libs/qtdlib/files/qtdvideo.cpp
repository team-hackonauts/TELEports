#include "qtdvideo.h"

QTdVideo::QTdVideo(QObject *parent)
    : QTdObject(parent)
    , m_duration(0)
    , m_width(0)
    , m_height(0)
    , m_thumbnail(new QTdThumbnail)
    , m_video(new QTdFile)
{
    setType(VIDEO);
}

qint32 QTdVideo::duration() const
{
    return m_duration;
}

qint32 QTdVideo::width() const
{
    return m_width;
}

qint32 QTdVideo::height() const
{
    return m_height;
}

QString QTdVideo::fileName() const
{
    return m_fileName;
}

QString QTdVideo::mimeType() const
{
    return m_mimeType;
}

QTdThumbnail *QTdVideo::thumbnail() const
{
    return m_thumbnail.data();
}

QTdFile *QTdVideo::video() const
{
    return m_video.data();
}

void QTdVideo::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_duration = qint32(json["duration"].toInt());
    m_width = qint32(json["width"].toInt());
    m_height = qint32(json["height"].toInt());
    m_fileName = json["file_name"].toString();
    m_mimeType = json["mime_type"].toString();
    if (json.contains("thumbnail")) {
        m_thumbnail->unmarshalJson(json["thumbnail"].toObject());
    }
    m_video->unmarshalJson(json["video"].toObject());
    emit videoChanged();
}
