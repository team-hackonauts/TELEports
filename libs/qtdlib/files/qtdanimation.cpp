#include "qtdanimation.h"

QTdAnimation::QTdAnimation(QObject *parent)
    : QTdObject(parent)
    , m_duration(0)
    , m_width(0)
    , m_height(0)
    , m_thumbnail(new QTdThumbnail)
    , m_minithumbnail(new QTdMiniThumbnail)
    , m_animation(new QTdFile)
{
    setType(ANIMATION);
}

qint32 QTdAnimation::duration() const
{
    return m_duration;
}

qint32 QTdAnimation::width() const
{
    return m_width;
}

qint32 QTdAnimation::height() const
{
    return m_height;
}

QString QTdAnimation::fileName() const
{
    return m_fileName;
}

QString QTdAnimation::mimeType() const
{
    return m_mimeType;
}

QTdThumbnail *QTdAnimation::thumbnail() const
{
    return m_thumbnail.data();
}

QTdMiniThumbnail *QTdAnimation::miniThumbnail() const
{
    return m_minithumbnail.data();
}

QTdFile *QTdAnimation::animation() const
{
    return m_animation.data();
}

void QTdAnimation::unmarshalJson(const QJsonObject &json)
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
    if (json.contains("minithumbnail")) {
        m_minithumbnail->unmarshalJson(json["minithumbnail"].toObject());
    }
    m_animation->unmarshalJson(json["animation"].toObject());
    emit animationChanged();
}
