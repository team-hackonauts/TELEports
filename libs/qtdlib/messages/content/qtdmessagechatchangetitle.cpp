#include "qtdmessagechatchangetitle.h"
#include "utils/i18n.h"

QTdMessageChatChangeTitle::QTdMessageChatChangeTitle(QObject *parent)
    : QTdMessageContent(parent)
{
    setType(MESSAGE_CHAT_CHANGE_TITLE);
}

QString QTdMessageChatChangeTitle::title() const
{
    return m_title;
}

void QTdMessageChatChangeTitle::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_title = json["title"].toString();
    m_typeText = gettext("changed the chat title");
    emit contentChanged();
}
