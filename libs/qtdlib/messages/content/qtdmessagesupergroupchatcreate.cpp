#include "qtdmessagesupergroupchatcreate.h"
#include <QDebug>
#include <QJsonArray>
#include "user/requests/qtdgetuserrequest.h"
#include "utils/await.h"
#include "utils/i18n.h"

QTdMessageSuperGroupChatCreate::QTdMessageSuperGroupChatCreate(QObject *parent)
    : QTdMessageContent(parent)
{
    setType(MESSAGE_SUPER_GROUP_CHAT_CREATE);
}

QString QTdMessageSuperGroupChatCreate::title() const
{
    return m_title;
}

void QTdMessageSuperGroupChatCreate::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_title = json["title"].toString();
    m_typeText = gettext("created this group");
    emit titleChanged();
}
