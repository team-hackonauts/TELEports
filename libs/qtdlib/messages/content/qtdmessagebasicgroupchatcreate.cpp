#include "qtdmessagebasicgroupchatcreate.h"
#include <QDebug>
#include <QJsonArray>
#include "user/requests/qtdgetuserrequest.h"
#include "utils/await.h"
#include "utils/i18n.h"

QTdMessageBasicGroupChatCreate::QTdMessageBasicGroupChatCreate(QObject *parent)
    : QTdMessageChatAddMembers(parent)
{
    setType(MESSAGE_BASIC_GROUP_CHAT_CREATE);
}

QString QTdMessageBasicGroupChatCreate::title() const
{
    return m_title;
}

void QTdMessageBasicGroupChatCreate::unmarshalJson(const QJsonObject &json)
{
    m_title = json["title"].toString();
    emit titleChanged();
    QTdMessageChatAddMembers::unmarshalJson(json);
    m_typeText = gettext("created this group");
    emit membersChanged();
}
