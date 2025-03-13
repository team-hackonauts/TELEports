#include "qtdsupergroupchat.h"
#include <QDateTime>
#include "chat/requests/qtdgetsupergrouprequest.h"
#include "chat/requests/qtdgetsupergroupfullinforequest.h"
#include "client/qtdclient.h"
#include "common/qabstracttdobject.h"
#include "utils/await.h"

QTdSuperGroupChat::QTdSuperGroupChat(QObject *parent)
    : QTdChat(parent)
    , m_sgId(0)
    , m_date(0)
    , m_status(Q_NULLPTR)
    , m_memberCount(0)
    , m_signMessages(false)
    , m_isChannel(false)
    , m_isVerified(false)
    , m_adminCount(0)
    , m_restrictedCount(0)
    , m_bannedCount(0)
    , m_canGetMembers(false)
    , m_canSetUsername(false)
    , m_canSetStickerSet(false)
    , m_historyAvailable(false)
    , m_stickerSet(0)
    , m_pinnedMessageId(0)
    , m_upgradeGroupId(0)
    , m_upgradeMaxMsgId(0)
{
    connect(QTdClient::instance(), &QTdClient::superGroup, this, &QTdSuperGroupChat::updateSuperGroup);
    connect(QTdClient::instance(), &QTdClient::updateSuperGroup, this, &QTdSuperGroupChat::updateSuperGroup);
    connect(QTdClient::instance(), &QTdClient::updateSupergroupFullInfo, this, &QTdSuperGroupChat::updateSuperGroupFullInfo);
}

QString QTdSuperGroupChat::qmlSuperGroupId() const
{
    return m_sgId.toQmlValue();
}

qint64 QTdSuperGroupChat::superGroupId() const
{
    return m_sgId.value();
}

QString QTdSuperGroupChat::userName() const
{
    return m_userNames->editableUsername();
}

QDateTime QTdSuperGroupChat::qmlDate() const
{
    return QDateTime::fromTime_t(m_date);
}

qint32 QTdSuperGroupChat::date() const
{
    return m_date;
}

QTdChatMemberStatus *QTdSuperGroupChat::status() const
{
    return m_status.data();
}

QString QTdSuperGroupChat::qmlMemberCount() const
{
    return m_memberCount.toQmlValue();
}

qint32 QTdSuperGroupChat::memberCount() const
{
    return m_memberCount.value();
}

bool QTdSuperGroupChat::signMessages() const
{
    return m_signMessages;
}

bool QTdSuperGroupChat::isChannel() const
{
    return m_isChannel;
}

bool QTdSuperGroupChat::isVerified() const
{
    return m_isVerified;
}

bool QTdSuperGroupChat::isWritable() const
{
    auto statusType = m_status->type();
    switch (statusType) {
        case QTdObject::Type::CHAT_MEMBER_STATUS_ADMIN: {
            if (m_isChannel) {
                auto adminStatus = qobject_cast<QTdChatMemberStatusAdministrator *>(m_status.data());
                if (adminStatus->rights())
                    return adminStatus->rights()->canPostMessages();
                else
                    return false;
            }
            return true;
        }
        case QTdObject::Type::CHAT_MEMBER_STATUS_CREATOR: {
            auto creatorStatus = qobject_cast<QTdChatMemberStatusCreator *>(m_status.data());
            return creatorStatus->isMember();
        }
        case QTdObject::Type::CHAT_MEMBER_STATUS_BANNED:
        case QTdObject::Type::CHAT_MEMBER_STATUS_LEFT: {
            return false;
        }
        case QTdObject::Type::CHAT_MEMBER_STATUS_MEMBER: {
            return !m_isChannel;
        }
        case QTdObject::Type::CHAT_MEMBER_STATUS_RESTRICTED: {
            auto restrictedStatus = qobject_cast<QTdChatMemberStatusRestricted *>(m_status.data());
            if (restrictedStatus->permissions()) {
                return restrictedStatus->isMember() && restrictedStatus->permissions()->canSendMessages();
            }
            return false;
        }
    }
    return false;
}

QString QTdSuperGroupChat::restrictionReason() const
{
    return m_restrictionReason;
}

QString QTdSuperGroupChat::description() const
{
    return m_description;
}

QString QTdSuperGroupChat::qmlAdminCount() const
{
    return m_adminCount.toQmlValue();
}

qint32 QTdSuperGroupChat::adminCount() const
{
    return m_adminCount.value();
}

QString QTdSuperGroupChat::qmlRestrictedCount() const
{
    return m_restrictedCount.toQmlValue();
}

qint32 QTdSuperGroupChat::restrictedCount() const
{
    return m_restrictedCount.value();
}

QString QTdSuperGroupChat::qmlBannedCount() const
{
    return m_bannedCount.toQmlValue();
}

qint32 QTdSuperGroupChat::bannedCount() const
{
    return m_bannedCount.value();
}

bool QTdSuperGroupChat::isHistoryAvailable() const
{
    return m_historyAvailable;
}

QString QTdSuperGroupChat::qmlStickerSetId() const
{
    return m_stickerSet.toQmlValue();
}

qint64 QTdSuperGroupChat::stickerSetId() const
{
    return m_stickerSet.value();
}

QString QTdSuperGroupChat::inviteLink() const
{
    return m_inviteLink;
}

QString QTdSuperGroupChat::qmlPinnedMessageId() const
{
    return m_pinnedMessageId.toQmlValue();
}

qint64 QTdSuperGroupChat::pinnedMessageId() const
{
    return m_pinnedMessageId.value();
}

QString QTdSuperGroupChat::qmlUpgradedFromBasicGroupId() const
{
    return m_upgradeGroupId.toQmlValue();
}

qint64 QTdSuperGroupChat::upgradedFromBasicGroupId() const
{
    return m_upgradeGroupId.value();
}

QString QTdSuperGroupChat::qmlUpgradedFromMaxMessageId() const
{
    return m_upgradeMaxMsgId.toQmlValue();
}

qint64 QTdSuperGroupChat::upgradedFromMaxMessageId() const
{
    return m_upgradeMaxMsgId.value();
}

void QTdSuperGroupChat::onChatDeserialized()
{
    getSuperGroupData();
}

void QTdSuperGroupChat::parseSuperGroupId() {
    QTdChatTypeSuperGroup *group = qobject_cast<QTdChatTypeSuperGroup *>(chatType());
    if (group && group->superGroupId() > 0) {
        m_sgId = group->superGroupId();
    }
}
void QTdSuperGroupChat::getSuperGroupFullInfo()
{
    if (m_sgId.value() == 0) {
        parseSuperGroupId();
    }
    QScopedPointer<QTdGetSuperGroupFullInfoRequest> req(new QTdGetSuperGroupFullInfoRequest);
    req->setSupergroupId(superGroupId());
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during fetching supergroup full info:" << resp.result().errorString();
        return;
    }
    superGroupFullInfo(resp.result().json());
}

void QTdSuperGroupChat::getSuperGroupData()
{
    if (m_sgId.value() == 0) {
        parseSuperGroupId();
    }
    QScopedPointer<QTdGetSuperGroupRequest> req(new QTdGetSuperGroupRequest);
    req->setSuperGroupId(superGroupId());
    QTdClient::instance()->send(req.data());
}

void QTdSuperGroupChat::updateSuperGroup(const QJsonObject &json)
{
    const qint64 gid = json["id"].toVariant().toLongLong();
    if (gid != superGroupId()) {
        return;
    }

    const QJsonObject status = json["status"].toObject();
    m_status.reset(QTdChatMemberStatusFactory::create(status, this));

    m_signMessages = json["sign_messages"].toBool();
    m_isChannel = json["is_channel"].toBool();
    m_isVerified = json["is_verified"].toBool();
    m_restrictionReason = json["restriction_reason"].toString();
    m_userNames.reset(new QTdUsernames(this));
    m_userNames->unmarshalJson(json["usernames"].toObject());
    emit isWritableChanged();
    emit superGroupChanged();
    emit chatStatusChanged();
    getSuperGroupFullInfo();
}

void QTdSuperGroupChat::updateSuperGroupFullInfo(const QJsonObject &json)
{
    const qint64 sid = json["supergroup_id"].toVariant().toLongLong();
    if (sid != superGroupId()) {
        return;
    }
    const QJsonObject info = json["supergroup_full_info"].toObject();
    superGroupFullInfo(info);
}

void QTdSuperGroupChat::superGroupFullInfo(const QJsonObject &info)
{
    m_description = info["description"].toString();
    m_memberCount = info["member_count"];
    m_adminCount = info["administrator_count"];
    m_restrictedCount = info["restricted_count"];
    m_bannedCount = info["banned_count"];
    m_canGetMembers = info["can_get_members"].toBool();
    m_canSetUsername = info["can_set_username"].toBool();
    m_canSetStickerSet = info["can_set_sticker_set"].toBool();
    m_historyAvailable = info["is_all_history_available"].toBool();
    m_stickerSet = info["sticker_set_id"];
    m_inviteLink = info["invite_link"].toString();
    m_upgradeGroupId = info["upgraded_from_basic_group_id"];
    m_upgradeMaxMsgId = info["upgraded_from_max_message_id"];
    emit superGroupInfoChanged();
}
