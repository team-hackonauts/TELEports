#include "qtdinputmessagedocument.h"

QTdInputMessageDocument::QTdInputMessageDocument(QObject *parent)
    : QTdInputMessageContentAttachmentCaption(parent)
    , m_document(QString())
    , m_caption(QString())
    , m_captionEntities(QJsonArray())
{
}
void QTdInputMessageDocument::setAttachmentPath(const QString &url)
{

    m_document = url;
}
void QTdInputMessageDocument::setCaption(const QString &caption)
{
    m_caption = caption;
}
void QTdInputMessageDocument::setCaptionEntities(const QJsonArray &entities)
{
    m_captionEntities = entities;
}
QJsonObject QTdInputMessageDocument::marshalJson()
{
    qDebug() << "inputMessageDocument";
    return QJsonObject{
        { "@type", "inputMessageDocument" },
        { "document", QJsonObject{
                           { "@type", "inputFileGenerated" },
                           { "original_path", m_document },
                           { "conversion", "attachment" } } },
        { "caption", QJsonObject{ { "@type", "formattedText" }, { "text", m_caption }, { "entities", m_captionEntities } } },
    };
}
