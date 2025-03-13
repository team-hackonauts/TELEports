#include "qtdmessagepinmessage.h"
#include "utils/i18n.h"

QTdMessagePinMessage::QTdMessagePinMessage(QObject *parent)
    : QTdMessageContent(parent)
    , m_message_id(0)
{
    setType(MESSAGE_PIN_MESSAGE);
}

qint64 QTdMessagePinMessage::message_id() const
{
    return m_message_id;
}

void QTdMessagePinMessage::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_message_id = json["message_id"].toVariant().toLongLong();
    m_typeText = gettext("Pinned Message");
}
