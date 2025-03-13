#include "qtdchatmember.h"

#include <QScopedPointer>

#include "user/qtdusers.h"
#include "client/qtdclient.h"
#include "qtdchatactionfactory.h"
#include "utils/await.h"
#include "user/requests/qtdgetuserrequest.h"

QTdChatMember::QTdChatMember(QObject *parent)
    : QTdObject(parent)
    , m_inviteUserId(0)
    , m_joinedChatDate(0)
    , m_status(Q_NULLPTR)
{
    setType(CHAT_MEMBER);
}

QTdMessageSender *QTdChatMember::memberId() const
{
    return m_memberId.data();
}

QString QTdChatMember::qmlInviteUserId() const
{
    return m_inviteUserId.toQmlValue();
}

qint64 QTdChatMember::inviteUserId() const
{
    return m_inviteUserId.value();
}

QDateTime QTdChatMember::qmlJoinedChatDate() const
{
    return QDateTime::fromTime_t(m_joinedChatDate.value());
}

qint32 QTdChatMember::joinedChatDate() const
{
    return m_joinedChatDate.value();
}

QTdChatMemberStatus *QTdChatMember::status() const
{
    return m_status.data();
}

void QTdChatMember::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_memberId.reset(QTdMessageSenderFactory::create(json["member_id"].toObject(), this));
    m_inviteUserId = json["inviter_user_id"].toVariant().toLongLong();
    m_joinedChatDate = json["joined_chat_date"];
    m_status.reset(QTdChatMemberStatusFactory::create(json["status"].toObject(), this));

    emit chatMemberChanged();
}
