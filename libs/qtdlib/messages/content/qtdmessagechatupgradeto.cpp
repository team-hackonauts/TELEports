#include "qtdmessagechatupgradeto.h"
#include "chat/requests/qtdgetsupergrouprequest.h"
#include "utils/await.h"
#include "utils/i18n.h"

QTdMessageChatUpgradeTo::QTdMessageChatUpgradeTo(QObject *parent)
    : QTdMessageContent(parent)

{
    setType(MESSAGE_CHAT_UPGRADE_TO);
}

QString QTdMessageChatUpgradeTo::qmlSuperGroupId() const
{
    return m_sgId.toQmlValue();
}

qint64 QTdMessageChatUpgradeTo::superGroupId() const
{
    return m_sgId.value();
}

void QTdMessageChatUpgradeTo::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    if (json.isEmpty()) {
        return;
    }
    m_sgId = json["supergroup_id"];
    m_typeText = gettext("upgraded to supergroup");
    emit contentChanged();
}
