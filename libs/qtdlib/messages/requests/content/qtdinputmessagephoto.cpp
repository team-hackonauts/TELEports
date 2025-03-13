#include <tuple>

#include "qtdinputmessagephoto.h"

QTdInputMessagePhoto::QTdInputMessagePhoto(QObject *parent)
    : QTdInputMessageContentAttachmentCaption(parent)
    , m_photo(QString())
    , m_width(0)
    , m_height(0)
    , m_caption(QString())
    , m_captionEntities(QJsonArray())
    , m_mediaSizeExtractor(new QTdMediaSizeExtractor(this))
    , m_inputThumbnail(Q_NULLPTR)
{
}

void QTdInputMessagePhoto::setAttachmentPath(const QString &url)
{   
    m_photo = url;
    m_inputThumbnail.reset(new QTdInputThumbnail(this));
    m_inputThumbnail->setOriginalFile(m_photo);
    auto mediaSize = m_mediaSizeExtractor->extractPictureSize(m_photo);
    m_width = std::get<0>(mediaSize);
    m_height = std::get<1>(mediaSize);
}

void QTdInputMessagePhoto::setCaption(const QString &caption)
{
    m_caption = caption;
}

void QTdInputMessagePhoto::setCaptionEntities(const QJsonArray &entities)
{
    m_captionEntities = entities;
}

QJsonObject QTdInputMessagePhoto::marshalJson()
{
    
    return QJsonObject{
        { "@type", "inputMessagePhoto" },
        { "photo", QJsonObject{
                { "@type", "inputFileGenerated" },
                { "original_path", m_photo },
                { "conversion", "attachment" } 
            }
        },
        { "width", m_width},
        { "height", m_height},
        { "thumbnail", m_inputThumbnail->marshalJson()},
        { "caption", QJsonObject{
                { "@type", "formattedText" },
                { "text", m_caption },
                { "entities", m_captionEntities }
            }
        }
    };
}
