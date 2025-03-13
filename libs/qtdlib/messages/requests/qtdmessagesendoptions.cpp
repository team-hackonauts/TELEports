#include "qtdmessagesendoptions.h"

QTdMessageSendOptions::QTdMessageSendOptions(QObject *parent)
    : QTdObject(parent)
    , m_disableNotifications(false)
    , m_sendDate(0)
{
    setType(MESSAGE_SEND_OPTIONS);
}

void QTdMessageSendOptions::setDisableNotifications(const bool value)
{
    m_disableNotifications = value;
}

void QTdMessageSendOptions::setSendDate(const qint32 value)
{
    m_sendDate = value;
}

QJsonObject QTdMessageSendOptions::marshalJson()
{
    auto result = QJsonObject{
        { "@type", "messageSendOptions" },
        { "disable_notification", m_disableNotifications }
    };
    if (m_sendDate > 0) {
        result.insert("scheduling_state", QJsonObject{
            { "@type", "messageSchedulingStateSendAtDate" },
            { "send_date", m_sendDate }
        });
    } else if (m_sendDate == -1) {
        result.insert("scheduling_state", QJsonObject{
            { "@type", "messageSchedulingStateSendWhenOnline" }
        });
    }
    return result;
}