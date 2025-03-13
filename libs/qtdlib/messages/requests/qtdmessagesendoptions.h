#ifndef QTDMESSAGESENDOPTIONS_H
#define QTDMESSAGESENDOPTIONS_H

#include <QObject>
#include "common/qabstracttdobject.h"

/**
 * @brief The QTdMessageSendOptions class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_send_options.html
 */
class QTdMessageSendOptions : public QTdObject
{
    Q_OBJECT

public:
    explicit QTdMessageSendOptions(QObject *parent = nullptr);

    void setDisableNotifications(const bool value);
    void setSendDate(const qint32 value);
    QJsonObject marshalJson();

signals:


private:
    Q_DISABLE_COPY(QTdMessageSendOptions)

    bool m_disableNotifications;
    bool m_fromBackground;
    qint32 m_sendDate;
};





#endif //QTDMESSAGESENDOPTIONS_H