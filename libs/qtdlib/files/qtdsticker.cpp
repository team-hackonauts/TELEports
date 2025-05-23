#include "qtdsticker.h"

QTdSticker::QTdSticker(QObject *parent)
    : QTdObject(parent)
    , m_setId(0)
    , m_width(0)
    , m_height(0)
    , m_isMask(false)
    , m_format(new QTdStickerFormat)
    , m_type(new QTdStickerType)
    , m_thumbnail(new QTdThumbnail)
    , m_sticker(new QTdFile)
{
    setType(STICKER);
}

QString QTdSticker::qmlSetId() const
{
    return m_setId.toQmlValue();
}

qint64 QTdSticker::setId() const
{
    return m_setId.value();
}

qint32 QTdSticker::width() const
{
    return m_width;
}

qint32 QTdSticker::height() const
{
    return m_height;
}

QString QTdSticker::emoji() const
{
    return m_emoji;
}

QTdFile *QTdSticker::sticker() const
{
    return m_sticker.data();
}

void QTdSticker::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_setId = json["set_id"];
    m_width = qint32(json["width"].toInt());
    m_height = qint32(json["height"].toInt());
    m_emoji = json["emoji"].toString();
    m_format.reset(QTdStickerFormatFactory::create(json["format"].toObject(), this));
    m_type.reset(QTdStickerTypeFactory::create(json["type"].toObject(), this));
    m_isMask = json["is_mask"].toBool();
    if (json.contains("thumbnail")) {
        m_thumbnail->unmarshalJson(json["thumbnail"].toObject());
    }
    m_sticker->unmarshalJson(json["sticker"].toObject());
    emit stickerChanged();
}

QTdThumbnail *QTdSticker::thumbnail() const
{
    return m_thumbnail.data();
}

bool QTdSticker::isMask() const
{
    return m_isMask;
}

QTdStickerType *QTdSticker::qmlType() const
{
    return m_type.data();
}

QTdStickerFormat *QTdSticker::qmlFormat() const
{
    return m_format.data();
}