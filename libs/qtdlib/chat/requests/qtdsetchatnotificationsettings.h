#ifndef QTDSETCHATNOTIFICATIONSETTINGS_H
#define QTDSETCHATNOTIFICATIONSETTINGS_H

#include <QObject>
#include "common/qtdrequest.h"
#include "../../notifications/qtdnotificationsettings.h"

/**
 * @brief The QTdCloseChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_chat_notification_settings.html
 */
class QTdSetChatNotificationSettings : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    QTdNotificationSettings *m_notificationSettings;

public:
    explicit QTdSetChatNotificationSettings(QObject *parent = nullptr);

    /**
     * @brief setChatId
     * @param id of chat to close
     */
    void setChatId(const qint64 &id);

    void setNotificationSettings(QTdNotificationSettings *settings);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();
};

#endif // QTDSETCHATNOTIFICATIONSETTINGS_H
