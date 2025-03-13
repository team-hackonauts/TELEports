#include "qtdmessagedocument.h"
#include "utils/i18n.h"

QTdMessageDocument::QTdMessageDocument(QObject *parent)
    : QTdMessageContent(parent)
    , m_document(new QTdDocument)
    , m_caption(new QTdFormattedText)
{
    setType(MESSAGE_DOCUMENT);
}

QTdDocument *QTdMessageDocument::document() const
{
    return m_document.data();
}
QTdFormattedText *QTdMessageDocument::caption() const
{
    return m_caption.data();
}
void QTdMessageDocument::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_document->unmarshalJson(json["document"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_infoText = m_caption->text() != "" ? m_caption->oneLineText() : "";
    m_typeText = m_document->fileName() + (m_caption->text() != "" ? "," : "");
}
