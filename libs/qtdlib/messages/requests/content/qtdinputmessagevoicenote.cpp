#include "qtdinputmessagevoicenote.h"

QTdInputMessageVoiceNote::QTdInputMessageVoiceNote(QObject *parent)
    : QTdInputMessageContent(parent)
    , m_voiceNote(QString())
    , m_duration(0)
    , m_waveform(QString())
    , m_caption(QString())
    , m_captionEntities(QJsonArray())
{
}
void QTdInputMessageVoiceNote::setAttachmentPath(const QString &url)
{
    m_voiceNote = url;
}
void QTdInputMessageVoiceNote::setDuration(const qint32 &duration)
{
    m_duration = duration;
}
void QTdInputMessageVoiceNote::setWaveform(const QString &waveform)
{
    m_waveform = waveform;
}
void QTdInputMessageVoiceNote::setCaption(const QString &caption)
{
    m_caption = caption;
}
void QTdInputMessageVoiceNote::setCaptionEntities(const QJsonArray &entities)
{
    m_captionEntities = entities;
}
QJsonObject QTdInputMessageVoiceNote::marshalJson()
{
    return QJsonObject {
        { "@type", "inputMessageVoiceNote" },
        { "voice_note", QJsonObject { { "@type", "inputFileGenerated" }, { "original_path", m_voiceNote }, { "conversion", "record_voice" } } },
        { "caption", QJsonObject { { "@type", "formattedText" }, { "text", m_caption }, { "entities", m_captionEntities } } },
    };
}
