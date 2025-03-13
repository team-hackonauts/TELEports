#include "qtdmessagephoto.h"
#include "utils/i18n.h"

QTdMessagePhoto::QTdMessagePhoto(QObject *parent)
    : QTdMessageContent(parent)
    , m_photo(new QTdPhotos)
    , m_caption(new QTdFormattedText)
{
    setType(MESSAGE_PHOTO);
}

QTdPhotos *QTdMessagePhoto::photo() const
{
    return m_photo.data();
}
QTdFormattedText *QTdMessagePhoto::caption() const
{
    return m_caption.data();
}
void QTdMessagePhoto::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_photo->unmarshalJson(json["photo"].toObject());
    m_caption->unmarshalJson(json["caption"].toObject());
    m_isSecret = json["is_secret"].toBool();
    m_infoImageUrl = QUrl("image://photo/" + m_photo->sizes()->at(0)->photo()->local()->path());
    m_infoText = m_caption->text() != "" ? m_caption->oneLineText() : "";
    m_typeText = m_caption->text() != "" ? gettext("Photo,") : gettext("Photo");
}
