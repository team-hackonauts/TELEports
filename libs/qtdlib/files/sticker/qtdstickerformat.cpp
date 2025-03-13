#include "qtdstickerformat.h"

#include <QDebug>

QTdStickerFormat::QTdStickerFormat(QObject *parent)
    : QTdObject(parent)
{

}

QTdStickerFormatWebp::QTdStickerFormatWebp(QObject *parent)
    : QTdStickerFormat(parent)
{
    setType(STICKER_FORMAT_WEBP);
}

QTdStickerFormatTgs::QTdStickerFormatTgs(QObject *parent)
    : QTdStickerFormat(parent)
{
    setType(STICKER_FORMAT_TGS);
}


QTdStickerFormatWebm::QTdStickerFormatWebm(QObject *parent)
    : QTdStickerFormat(parent)
{
    setType(STICKER_FORMAT_WEBM);
}

QTdStickerFormat *QTdStickerFormatFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();

    QTdStickerFormat *result;

    if (type == "stickerFormatWebp") {
        result = new QTdStickerFormatWebp(parent);
    } else if (type == "stickerFormatTgs") {
        result = new QTdStickerFormatTgs(parent);
    } else if (type == "stickerFormatWebm") {
        result = new QTdStickerFormatWebm(parent);
    } else {
        qWarning() << "Received unknown sticker type" << type << json;
        return new QTdStickerFormat(parent);
    }
    result->unmarshalJson(json);
    return result;
}