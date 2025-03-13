#include "qtdthumbnailformat.h"

QTdThumbnailFormat::QTdThumbnailFormat(QObject *parent)
    : QTdObject(parent)
{
}

QTdThumbnailFormat *QTdThumbnailFormat::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();

    if (type == "thumbnailFormatGif") {
        return new QTdThumbnailFormatGif(parent);
    } else if (type == "thumbnailFormatJpeg") {
        return new QTdThumbnailFormatJpeg(parent);
    } else if (type == "thumbnailFormatMpeg4") {
        return new QTdThumbnailFormatMpeg4(parent);
    } else if (type == "thumbnailFormatPng") {
        return new QTdThumbnailFormatPng(parent);
    } else if (type == "thumbnailFormatTgs") {
        return new QTdThumbnailFormatTgs(parent);
    } else if (type == "thumbnailFormatWebp") {
        return new QTdThumbnailFormatWebp(parent);
    }

    return nullptr;
}

QTdThumbnailFormatGif::QTdThumbnailFormatGif(QObject *parent)
    : QTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_GIF);
}

QTdThumbnailFormatJpeg::QTdThumbnailFormatJpeg(QObject *parent)
    : QTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_JPEG);
}

QTdThumbnailFormatMpeg4::QTdThumbnailFormatMpeg4(QObject *parent)
    : QTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_MPEG4);
}

QTdThumbnailFormatPng::QTdThumbnailFormatPng(QObject *parent)
    : QTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_PNG);
}

QTdThumbnailFormatTgs::QTdThumbnailFormatTgs(QObject *parent)
    : QTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_TGS);
}

QTdThumbnailFormatWebp::QTdThumbnailFormatWebp(QObject *parent)
    : QTdThumbnailFormat(parent)
{
    setType(THUMBNAIL_FORMAT_WEBP);
}
