#ifndef QTDMESSAGESUPERGROUPCHATCREATE_H
#define QTDMESSAGESUPERGROUPCHATCREATE_H

#include <QObject>
#include "models/QmlObjectListModel.h"
#include "messages/qtdmessagecontent.h"
#include "qtdmessagechataddmembers.h"
#include "user/qtdusers.h"

/**
 * @brief The QTdMessageBasicGroupChatCreate class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_super_group_chat_create.html
 */
class QTdMessageSuperGroupChatCreate : public QTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageSuperGroupChatCreate)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
public:
    explicit QTdMessageSuperGroupChatCreate(QObject *parent = nullptr);

    QString title() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void titleChanged();

private:
    QString m_title;
};

#endif // QTDMESSAGESUPERGROUPCHATCREATE_H
