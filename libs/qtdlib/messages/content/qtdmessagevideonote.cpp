#include "qtdmessagevideonote.h"
#include "utils/i18n.h"

QTdMessageVideoNote::QTdMessageVideoNote(QObject *parent)
    : QTdMessageContent(parent)
    , m_videoNote(new QTdVideoNote)
    , m_isViewed(new bool)
{
    setType(MESSAGE_VIDEO_NOTE);
}

QTdVideoNote *QTdMessageVideoNote::videoNote() const
{
    return m_videoNote.data();
}
bool QTdMessageVideoNote::isViewed() const
{
    return m_isViewed;
}

void QTdMessageVideoNote::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_videoNote->unmarshalJson(json["video_note"].toObject());
    m_isViewed = json["is_viewed"].toBool();
    m_isSecret = json["is_secret"].toBool();
    m_typeText = gettext("Video message");
    m_infoImageUrl = QUrl("image://photo/" + m_videoNote->thumbnail()->file()->local()->path());
}
