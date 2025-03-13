#include "qtdinputmessagetext.h"
#include "../../content/qtdformattedtext.h"

QTdInputMessageText::QTdInputMessageText(QObject *parent)
    : QTdInputMessageContent(parent)
    , m_text(QString())
    , m_entities(QJsonArray())
    , m_disable_web_page_preview(new bool)
    , m_clear_draft(false)
{
}

void QTdInputMessageText::setText(const QString &text)
{
    m_text = text;
}
void QTdInputMessageText::setClearDraft(const bool clear_draft)
{
    m_clear_draft = clear_draft;
}
void QTdInputMessageText::setEntities(const QJsonArray &entities)
{
    m_entities = entities;
}
QJsonObject QTdInputMessageText::marshalJson()
{
    return QJsonObject {
        { "@type", "inputMessageText" },
        { "text", QJsonObject { { "@type", "formattedText" }, { "text", m_text }, { "entities", m_entities } } },
        { "disable_web_page_preview", false },
        { "clear_draft", m_clear_draft }
    };
}

QString QTdInputMessageText::text() const
{
    return m_text;
}
bool QTdInputMessageText::clearDraft() const
{
    return m_clear_draft;
}
bool QTdInputMessageText::disableWebPagePreview() const
{
    return m_disable_web_page_preview;
}

void QTdInputMessageText::unmarshalJson(const QJsonObject &json)
{
    QTdInputMessageContent::unmarshalJson(json);
    m_clear_draft = json["clear_draft"].toBool();
    m_disable_web_page_preview = json["m_disable_web_page_preview"].toBool();
    QScopedPointer<QTdFormattedText> formattedText(new QTdFormattedText);
    formattedText->unmarshalJson(json["text"].toObject());
    m_text = formattedText->text();
    emit inputMessageTextChanged();
}
