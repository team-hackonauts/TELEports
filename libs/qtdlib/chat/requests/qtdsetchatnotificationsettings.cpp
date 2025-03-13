#include "qtdsetchatnotificationsettings.h"

QTdSetChatNotificationSettings::QTdSetChatNotificationSettings(QObject *parent)
    : QTdOkRequest(parent)
    , m_chatId(0)
{
}

void QTdSetChatNotificationSettings::setChatId(const qint64 &id)
{
    m_chatId = id;
}

void QTdSetChatNotificationSettings::setNotificationSettings(QTdNotificationSettings *settings)
{
    m_notificationSettings = settings;
}

QJsonObject QTdSetChatNotificationSettings::marshalJson()
{
    return QJsonObject{
        { "@type", "setChatNotificationSettings" },
        { "chat_id", m_chatId },
        { "notification_settings", m_notificationSettings->marshalJson() }
    };
}
