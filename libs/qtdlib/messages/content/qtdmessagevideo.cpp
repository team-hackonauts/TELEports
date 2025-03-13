#include "qtdmessagevideo.h"
#include "utils/i18n.h"

QTdMessageVideo::QTdMessageVideo(QObject *parent)
    : QTdMessageContent(parent)
    , m_video(new QTdVideo)
    , m_caption(new QTdFormattedText)
{
    setType(MESSAGE_VIDEO);
}

QTdVideo *QTdMessageVideo::video() const
{
    return m_video.data();
}
QTdFormattedText *QTdMessageVideo::caption() const
{
    return m_caption.data();
}
void QTdMessageVideo::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_video->unmarshalJson(json["video"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_isSecret = json["is_secret"].toBool();
    m_infoText = m_caption->text() != "" ? m_caption->text() : "";
    m_typeText = m_caption->text() != "" ? gettext("Video,") : gettext("Video");
    m_infoImageUrl = QUrl("image://photo/" + m_video->thumbnail()->file()->local()->path());
}
