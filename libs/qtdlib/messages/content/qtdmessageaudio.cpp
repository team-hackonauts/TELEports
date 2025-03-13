#include "qtdmessageaudio.h"
#include "utils/i18n.h"

QTdMessageAudio::QTdMessageAudio(QObject *parent)
    : QTdMessageContent(parent)
    , m_audio(new QTdAudio)
    , m_caption(new QTdFormattedText)
{
    setType(MESSAGE_AUDIO);
}

QTdAudio *QTdMessageAudio::audio() const
{
    return m_audio.data();
}
QTdFormattedText *QTdMessageAudio::caption() const
{
    return m_caption.data();
}
void QTdMessageAudio::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_audio->unmarshalJson(json["audio"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_infoText = m_caption->text() != "" ? m_caption->oneLineText() : "";
    m_typeText = QString("%1 - %2%3").arg(m_audio->performer(), m_audio->title(), m_caption->text() != "" ? "," : "");
    m_infoImageUrl = QUrl("file://" + m_audio->albumCoverThumbnail()->file()->local()->path());
}
