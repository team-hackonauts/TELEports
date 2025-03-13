#include "qtdbasicgroupchat.h"
#include <QDebug>
#include <QJsonArray>
#include <QScopedPointer>
#include "chat/requests/qtdgetbasicgrouprequest.h"
#include "client/qtdclient.h"

QTdBasicGroupChat::QTdBasicGroupChat(QObject *parent)
    : QTdChat(parent)
    , m_groupId(0)
    , m_memberCount(0)
    , m_status(Q_NULLPTR)
    , m_isActive(false)
    , m_upgradedSGID(0)
    , m_creatorId(0)
    , m_members(Q_NULLPTR)
{
    m_members = new QQmlObjectListModel<QTdChatMember>(this, "", "userId");
    connect(QTdClient::instance(), &QTdClient::basicGroup, this, &QTdBasicGroupChat::updateGroupData);
    connect(QTdClient::instance(), &QTdClient::updateBasicGroup, this, &QTdBasicGroupChat::updateGroupData);
    connect(QTdClient::instance(), &QTdClient::updateBasicGroupFullInfo, this, &QTdBasicGroupChat::updateGroupInfo);
}

QString QTdBasicGroupChat::qmlGroupId() const
{
    return m_groupId.toQmlValue();
}

qint64 QTdBasicGroupChat::groupId() const
{
    return m_groupId.value();
}

QString QTdBasicGroupChat::qmlMemberCount() const
{
    return m_memberCount.toQmlValue();
}

qint32 QTdBasicGroupChat::memberCount() const
{
    return m_memberCount.value();
}

QTdChatMemberStatus *QTdBasicGroupChat::status() const
{
    return m_status.data();
}

bool QTdBasicGroupChat::isActive() const
{
    return m_isActive;
}

QString QTdBasicGroupChat::qmlUpgradedToSuperGroupId() const
{
    return m_upgradedSGID.toQmlValue();
}

qint64 QTdBasicGroupChat::upgradedToSuperGroupId() const
{
    return m_upgradedSGID.value();
}

QString QTdBasicGroupChat::qmlCreatorUserId() const
{
    return m_creatorId.toQmlValue();
}

qint64 QTdBasicGroupChat::creatorUserId() const
{
    return m_creatorId.value();
}

QObject *QTdBasicGroupChat::qmlMembers() const
{
    return m_members;
}

QQmlObjectListModel<QTdChatMember> *QTdBasicGroupChat::members() const
{
    return m_members;
}

QString QTdBasicGroupChat::inviteLink() const
{
    return m_inviteLink;
}

void QTdBasicGroupChat::unmarshalJson(const QJsonObject &json)
{
    QTdChat::unmarshalJson(json);
    if (m_status.isNull()) {
        requestGroupData();
    }
}

void QTdBasicGroupChat::onChatDeserialized()
{
    requestGroupData();
}

void QTdBasicGroupChat::requestGroupData()
{
    QTdChatTypeBasicGroup *group = qobject_cast<QTdChatTypeBasicGroup *>(chatType());
    if (group->basicGroupId() > 0) {
        QScopedPointer<QTdGetBasicGroupRequest> req(new QTdGetBasicGroupRequest);
        req->setGroupId(group->basicGroupId());
        QTdClient::instance()->send(req.data());
    }
}

void QTdBasicGroupChat::updateGroupData(const QJsonObject &json)
{
    QTdChatTypeBasicGroup *group = qobject_cast<QTdChatTypeBasicGroup *>(chatType());
    const qint64 gid = json["id"].toVariant().toLongLong();
    if (gid != group->basicGroupId()) {
        return;
    }
    m_groupId = gid;
    m_memberCount = json["member_count"];

    const QJsonObject status = json["status"].toObject();
    m_status.reset(QTdChatMemberStatusFactory::create(status, this));

    m_isActive = json["is_active"].toBool();
    m_upgradedSGID = json["upgraded_to_supergroup_id"];
    emit groupChanged();
    emit chatStatusChanged();
}

void QTdBasicGroupChat::updateGroupInfo(const QJsonObject &json)
{
    const qint64 gid = json["basic_group_id"].toVariant().toLongLong();
    if (gid != groupId()) {
        return;
    }
    // We always update the full list in one go so clear all
    // the current members
    m_members->clear();

    const QJsonObject info = json["basic_group_full_info"].toObject();
    m_creatorId = info["creator_user_id"].toVariant().toLongLong();
    m_inviteLink = info["invite_link"].toString();

    const QJsonArray members = info["members"].toArray();
    for (const QJsonValue &memberData : members) {
        auto *member = new QTdChatMember;
        member->unmarshalJson(memberData.toObject());
        m_members->append(member);
    }

    emit groupInfoChanged();
}
