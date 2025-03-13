#include "qtdstickertype.h"

#include <QDebug>

QTdStickerType::QTdStickerType(QObject *parent)
    : QTdObject(parent)
{

}

QTdStickerTypeRegular::QTdStickerTypeRegular(QObject *parent)
    : QTdStickerType(parent)
{
    setType(STICKER_TYPE_REGULAR);
}

QTdStickerTypeMask::QTdStickerTypeMask(QObject *parent)
    : QTdStickerType(parent)
{
    setType(STICKER_TYPE_MASK);
}


QTdStickerTypeCustomEmoji::QTdStickerTypeCustomEmoji(QObject *parent)
    : QTdStickerType(parent)
{
    setType(STICKER_TYPE_CUSTOM_EMOJI);
}

QTdStickerType *QTdStickerTypeFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();

    QTdStickerType *result;

    if (type == "stickerTypeRegular") {
        result = new QTdStickerTypeRegular(parent);
    } else if (type == "stickerTypeMask") {
        result = new QTdStickerTypeMask(parent);
    } else if (type == "stickerTypeCustomEmoji") {
        result = new QTdStickerTypeCustomEmoji(parent);
    } else {
        qWarning() << "Received unknown sticker type" << type << json;
        return new QTdStickerType(parent);
    }
    result->unmarshalJson(json);
    return result;
}