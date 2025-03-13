#ifndef QTDMESSAGECHATADDMEMBERS_H
#define QTDMESSAGECHATADDMEMBERS_H

#include <QObject>
#include "models/QmlObjectListModel.h"
#include "messages/qtdmessagecontent.h"
#include "user/qtdusers.h"

/**
 * @brief The QTdMessageChatAddMembers class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_chat_add_members.html
 */
class QTdMessageChatAddMembers : public QTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageChatAddMembers)
    Q_PROPERTY(QObject *members READ members NOTIFY membersChanged)
    Q_PROPERTY(qint64 firstMemberId READ firstMemberId NOTIFY membersChanged)

public:
    explicit QTdMessageChatAddMembers(QObject *parent = nullptr);

    QObject *members() const;

    QList<qint64> memberUserIds() const;
    qint64 firstMemberId() const;
    void setSenderUserId(const qint64 senderUserId);

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void membersChanged();

private:
    void updateTypeText();
    QScopedPointer<QTdUsersSortFilterModel> m_model;
    QList<qint64> m_member_user_ids;
    qint64 m_senderUserId;
};

#endif // QTDMESSAGECHATADDMEMBERS_H
