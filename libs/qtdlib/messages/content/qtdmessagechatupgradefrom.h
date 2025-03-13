#ifndef QTDMESSAGECHATUPGRADEFROM_H
#define QTDMESSAGECHATUPGRADEFROM_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

/**
 * @brief The QTdMessageChatUpgradeFrom class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_chat_upgrade_from.html
 */
class QTdMessageChatUpgradeFrom : public QTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageChatUpgradeFrom)
    Q_PROPERTY(QString title READ title NOTIFY contentChanged)
    Q_PROPERTY(QString basicGroupId READ qmlBasicGroupId NOTIFY contentChanged)
public:
    explicit QTdMessageChatUpgradeFrom(QObject *parent = nullptr);
    QString title() const;
    QString qmlBasicGroupId() const;
    qint64 basicGroupId() const;
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    QString m_title;
    QTdInt64 m_groupdId;
};

#endif // QTDMESSAGECHATUPGRADEFROM_H
