#include "qtdmessageanimation.h"
#include "utils/i18n.h"

QTdMessageAnimation::QTdMessageAnimation(QObject *parent)
    : QTdMessageContent(parent)
    , m_animation(new QTdAnimation)
    , m_caption(new QTdFormattedText)
{
    setType(MESSAGE_ANIMATION);
}

QTdAnimation *QTdMessageAnimation::animation() const
{
    return m_animation.data();
}
QTdFormattedText *QTdMessageAnimation::caption() const
{
    return m_caption.data();
}
void QTdMessageAnimation::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_animation->unmarshalJson(json["animation"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_isSecret = json["is_secret"].toBool();
    m_infoText = m_caption->text() != "" ? m_caption->oneLineText() : "";
    m_typeText = m_caption->text() != "" ? gettext("GIF,") : gettext("GIF");
    m_infoImageUrl = QUrl("file://" + m_animation->thumbnail()->file()->local()->path());
}
