#include "qtdmessagechatchangephoto.h"
#include "utils/i18n.h"

QTdMessageChatChangePhoto::QTdMessageChatChangePhoto(QObject *parent)
    : QTdMessageContent(parent)
    , m_photo(new QTdPhotos)
{
    setType(MESSAGE_CHAT_CHANGE_PHOTO);
}

QTdPhotos *QTdMessageChatChangePhoto::photo() const
{
    return m_photo.data();
}

void QTdMessageChatChangePhoto::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    if (json.contains("photo")) {
        m_photo->unmarshalJson(json["photo"].toObject());
        m_typeText = gettext("changed the chat photo");
        emit contentChanged();
    }
}
