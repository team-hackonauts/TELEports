#ifndef QTDTHUMBNAILFORMAT_H
#define QTDTHUMBNAILFORMAT_H

#include "common/qabstracttdobject.h"

/**
 * @brief The QTdThumbnailFormat class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_thumbnail_format.html
 */
class QTdThumbnailFormat : public QTdObject
{
    Q_OBJECT
public:
    explicit QTdThumbnailFormat(QObject *parent = nullptr);

    static QTdThumbnailFormat *create(const QJsonObject &json, QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QTdThumbnailFormat)
};

/**
 * @brief The QTdThumbnailFormatGif class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_gif.html
 */
class QTdThumbnailFormatGif : public QTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QTdThumbnailFormatGif(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QTdThumbnailFormatGif)
};

/**
 * @brief The QTdThumbnailFormatJpeg class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_jpeg.html
 */
class QTdThumbnailFormatJpeg : public QTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QTdThumbnailFormatJpeg(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QTdThumbnailFormatJpeg)
};

/**
 * @brief The QTdThumbnailFormatMpeg4 class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_mpeg4.html
 */
class QTdThumbnailFormatMpeg4 : public QTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QTdThumbnailFormatMpeg4(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QTdThumbnailFormatMpeg4)
};

/**
 * @brief The QTdThumbnailFormatPng class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_png.html
 */
class QTdThumbnailFormatPng : public QTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QTdThumbnailFormatPng(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QTdThumbnailFormatPng)
};

/**
 * @brief The QTdThumbnailFormatTgs class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_tgs.html
 */
class QTdThumbnailFormatTgs : public QTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QTdThumbnailFormatTgs(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QTdThumbnailFormatTgs)
};

/**
 * @brief The QTdThumbnailFormatWebp class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1thumbnail_format_webp.html
 */
class QTdThumbnailFormatWebp : public QTdThumbnailFormat
{
    Q_OBJECT
public:
    explicit QTdThumbnailFormatWebp(QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(QTdThumbnailFormatWebp)
};

#endif // QTDTHUMBNAILFORMAT_H
