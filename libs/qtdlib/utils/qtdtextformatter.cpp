#include "qtdtextformatter.h"
#include <QCoreApplication>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QStringBuilder>

QTdTextFormatter::QTdTextFormatter(QObject *parent)
    : QObject(parent)
    , m_textDocument(Q_NULLPTR)
    , m_content(Q_NULLPTR)
{
    connect(this, &QTdTextFormatter::contentChanged, this, &QTdTextFormatter::doFormat);
    m_codeColor = QColor("#798eaf");
    m_linkColor = QColor("#5d84c1");
}

QQuickTextDocument *QTdTextFormatter::textDocument() const
{
    return m_textDocument;
}

QTdFormattedText *QTdTextFormatter::content() const
{
    return m_content;
}

QColor QTdTextFormatter::linkColor() const
{
    return m_linkColor;
}

QColor QTdTextFormatter::codeColor() const
{
    return m_codeColor;
}

QColor QTdTextFormatter::spoilerForeground() const
{
    return m_spoilerForeground;
}

QColor QTdTextFormatter::spoilerBackground() const
{
    return m_spoilerBackground;
}

void QTdTextFormatter::setTextDocument(QQuickTextDocument *textDocument)
{
    if (m_textDocument == textDocument)
        return;

    m_textDocument = textDocument;
    emit textDocumentChanged(m_textDocument);
}

void QTdTextFormatter::setContent(QTdFormattedText *content)
{
    if (m_content == content)
        return;

    m_content = content;
    emit contentChanged(m_content);
}

void QTdTextFormatter::setLinkColor(QColor newColor)
{
    if (m_linkColor == newColor)
        return;

    m_linkColor = newColor;
    emit textColorsChanged();
}

void QTdTextFormatter::setCodeColor(QColor newColor)
{
    if (m_codeColor == newColor)
        return;

    m_codeColor = newColor;
    emit textColorsChanged();
}

void QTdTextFormatter::setSpoilerForeground(QColor newColor)
{
    if (m_spoilerForeground == newColor)
        return;

    m_spoilerForeground = newColor;
    emit textColorsChanged();
}

void QTdTextFormatter::setSpoilerBackground(QColor newColor)
{
    if (m_spoilerBackground == newColor)
        return;

    m_spoilerBackground = newColor;
    emit textColorsChanged();
}

void QTdTextFormatter::doFormat()
{
    if (!m_textDocument->textDocument() || !m_content) {
        return;
    }
    
    const QList<QTdTextEntity *> entities = m_content->entities()->toList();
    QTextDocument *doc = m_textDocument->textDocument();
    if (doc->isEmpty()) {
        return;
    }
    const QString rawText = doc->toRawText();
    QTextCursor cursor { doc };
    for (const QTdTextEntity *entity : entities) {
        QTextCharFormat format;
        cursor.setPosition(entity->offset(), QTextCursor::MoveAnchor);
        cursor.setPosition(entity->offset() + entity->length(), QTextCursor::KeepAnchor);
        const QString subText = rawText.mid(entity->offset(), entity->length());
        switch (entity->entityType()->type()) {
        case QTdTextEntity::TEXT_ENTITY_TYPE_BOLD: {
            format.setFontWeight(60);
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_STRIKETHROUGH: {
            format.setFontStrikeOut(true);
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_UNDERLINE: {
            format.setFontUnderline(true);
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_BOT_COMMAND:
        case QTdTextEntity::TEXT_ENTITY_TYPE_CASHTAG:
            break;
        case QTdTextEntity::TEXT_ENTITY_TYPE_CODE:
        case QTdTextEntity::TEXT_ENTITY_TYPE_PRE:
        case QTdTextEntity::TEXT_ENTITY_TYPE_PRE_CODE: {
            format.setFontFamily("Ubuntu Mono");
            format.setFontFixedPitch(true);
            if (m_codeColor.isValid()) {
                format.setForeground(m_codeColor);
            }
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_EMAIL_ADDRESS: {
            format.setAnchor(true);
            format.setAnchorHref("mailto:" % subText);
            if (m_linkColor.isValid()) {
                format.setForeground(m_linkColor);
            }
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_ITALIC: {
            format.setFontItalic(true);
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_HASHTAG:
        case QTdTextEntity::TEXT_ENTITY_TYPE_MENTION:
        case QTdTextEntity::TEXT_ENTITY_TYPE_MENTION_NAME: {
            format.setAnchor(true);
            format.setAnchorHref(subText);
            if (m_linkColor.isValid()) {
                format.setForeground(m_linkColor);
            }
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_PHONE_NUMBER: {
            format.setAnchor(true);
            format.setAnchorHref("tel:" % subText);
            if (m_linkColor.isValid()) {
                format.setForeground(m_linkColor);
            }
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_TEXT_URL: {
            format.setAnchor(true);
            auto textUrlEntity = static_cast<const QTdTextEntityTypeTextUrl *>(entity->entityType());
            format.setAnchorHref(textUrlEntity->additionalInfo());
            format.setFontUnderline(true);
            if (m_linkColor.isValid()) {
                format.setForeground(m_linkColor);
            }
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_URL: {
            format.setAnchor(true);
            format.setAnchorHref(subText);
            format.setFontUnderline(true);
            if (m_linkColor.isValid()) {
                format.setForeground(m_linkColor);
            }
            cursor.mergeCharFormat(format);
            break;
        }
        case QTdTextEntity::TEXT_ENTITY_TYPE_SPOILER: {
            format.setForeground(m_spoilerForeground);
            format.setBackground(m_spoilerBackground);
            cursor.mergeCharFormat(format);
            break;
        }
        default:
            break;
        }
    }
}
