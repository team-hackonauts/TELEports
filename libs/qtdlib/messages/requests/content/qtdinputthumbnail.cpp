#include <tuple>

#include <QJsonObject>
#include <QDebug>

#include "qtdinputthumbnail.h"

QTdInputThumbnail::QTdInputThumbnail(QObject *parent)
    : QTdObject(parent)
    , m_width(0)
    , m_height(0)
    , m_thumbnailExtractor(new QTdThumbnailExtractor(this))
{
}

void QTdInputThumbnail::setOriginalFile(QString originalFile)
{
    auto result = m_thumbnailExtractor->extractThumbnail(originalFile, 320);
    m_thumbnailFile = std::get<0>(result);
    m_width = std::get<1>(result);
    m_height = std::get<2>(result);
}

qint32 QTdInputThumbnail::width()
{
    return m_width;
}

qint32 QTdInputThumbnail::height()
{
    return m_height;
}

QJsonObject QTdInputThumbnail::marshalJson()
{
    return QJsonObject {
        { "@type", "inputThumbnail" },
        { "thumbnail", QJsonObject {
                { "@type", "inputFileLocal" },
                { "path", m_thumbnailFile }
            }
        },
        { "width", m_width },
        { "height", m_height }
    };
}

