#include "qtdvoicenote.h"
#include <QTime>

QTdVoiceNote::QTdVoiceNote(QObject *parent)
    : QTdObject(parent)
    , m_duration(0)
    , m_voice(new QTdFile)
{
    setType(VOICE_NOTE);
}

qint32 QTdVoiceNote::duration() const
{
    return m_duration;
}

QString QTdVoiceNote::waveform() const
{
    return m_waveform;
}

QString QTdVoiceNote::mimeType() const
{
    return m_mimeType;
}

QString QTdVoiceNote::qmlDuration() const
{
    qint32 totalHours = (qint32)m_duration / 3600;
    if (totalHours > 0) {
        return QTime(0, 0, 0, 0).addSecs(m_duration).toString("hh:mm:ss");
    } else {
        return QTime(0, 0, 0, 0).addSecs(m_duration).toString("mm:ss");
    }
}

QTdFile *QTdVoiceNote::voice() const
{
    return m_voice.data();
}

void QTdVoiceNote::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_duration = qint32(json["duration"].toInt());
    m_waveform = json["waveform"].toString();
    m_mimeType = json["mime_type"].toString();
    m_voice->unmarshalJson(json["voice"].toObject());
    emit voiceNoteChanged();
}
