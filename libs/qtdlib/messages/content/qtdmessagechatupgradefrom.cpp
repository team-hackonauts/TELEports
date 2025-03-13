#include "qtdmessagechatupgradefrom.h"
#include "utils/i18n.h"

QTdMessageChatUpgradeFrom::QTdMessageChatUpgradeFrom(QObject *parent)
    : QTdMessageContent(parent)
{
    setType(MESSAGE_CHAT_UPGRADE_FROM);
}

QString QTdMessageChatUpgradeFrom::title() const
{
    return m_title;
}

QString QTdMessageChatUpgradeFrom::qmlBasicGroupId() const
{
    return m_groupdId.toQmlValue();
}

qint64 QTdMessageChatUpgradeFrom::basicGroupId() const
{
    return m_groupdId.value();
}

void QTdMessageChatUpgradeFrom::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_title = json["title"].toString();
    m_groupdId = json["basic_group_id"];
    m_typeText = gettext("upgraded to supergroup");
    emit contentChanged();
}
