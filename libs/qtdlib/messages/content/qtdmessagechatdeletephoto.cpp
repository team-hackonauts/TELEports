#include "qtdmessagechatdeletephoto.h"
#include "utils/i18n.h"

QTdMessageChatDeletePhoto::QTdMessageChatDeletePhoto(QObject *parent)
    : QTdMessageContent(parent)
{
    setType(MESSAGE_CHAT_DELETE_PHOTO);
    m_typeText = gettext("deleted the chat photo");
}
