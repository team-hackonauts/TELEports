#include "chat/qtdchattype.h"
#include "client/qtdclient.h"
#include "user/qtdusers.h"
#include "qtdchattype.h"

QTdChatType::QTdChatType(QObject *parent)
    : QTdObject(parent)
{
}

QTdChatTypeBasicGroup::QTdChatTypeBasicGroup(QObject *parent)
    : QTdChatType(parent)
    , m_groupId(0)
{
    setType(CHAT_TYPE_BASIC_GROUP);
}

QString QTdChatTypeBasicGroup::qmlBasicGroupId() const
{
    return m_groupId.toQmlValue();
}

qint64 QTdChatTypeBasicGroup::basicGroupId() const
{
    return m_groupId.value();
}

void QTdChatTypeBasicGroup::unmarshalJson(const QJsonObject &json)
{
    QTdChatType::unmarshalJson(json);
    m_groupId = json["basic_group_id"];
    emit groupIdChanged();
}

QTdChatTypePrivate::QTdChatTypePrivate(QObject *parent)
    : QTdChatType(parent)
    , m_userId(0)
    , m_waitingForUser(false)
{
    setType(CHAT_TYPE_PRIVATE);
}

QString QTdChatTypePrivate::qmlUserId() const
{
    return m_userId.toQmlValue();
}

qint64 QTdChatTypePrivate::userId() const
{
    return m_userId.value();
}

QTdUser *QTdChatTypePrivate::user() const
{
    return m_user;
}

void QTdChatTypePrivate::unmarshalJson(const QJsonObject &json)
{
    QTdChatType::unmarshalJson(json);
    m_userId = json["user_id"].toVariant().toLongLong();
    emit userIdChanged();
    updateUser(m_userId.value());
}

void QTdChatTypePrivate::updateUser(const qint64 &userId)
{
    if (userId != m_userId.value()) {
        return;
    }
    if (m_user) {
        m_user = Q_NULLPTR;
    }

    auto *users = QTdUsers::instance()->model();
    m_user = users->getByUid(QString::number(userId));
    if (m_user) {
        emit userChanged();
        if (m_waitingForUser) {
            disconnect(QTdUsers::instance(), &QTdUsers::userCreated, this, &QTdChatTypePrivate::updateUser);
            m_waitingForUser = false;
        }
        return;
    }
    connect(QTdUsers::instance(), &QTdUsers::userCreated, this, &QTdChatTypePrivate::updateUser);
    QTdClient::instance()->send(QJsonObject{
            { "@type", "getUser" },
            { "user_id", m_userId.value() } });
    m_waitingForUser = true;
}

QTdChatTypeSecret::QTdChatTypeSecret(QObject *parent)
    : QTdChatTypePrivate(parent)
    , m_chatId(0)
{
    setType(CHAT_TYPE_SECRET);
}

QString QTdChatTypeSecret::qmlSecretChatId() const
{
    return m_chatId.toQmlValue();
}

qint64 QTdChatTypeSecret::secretChatId() const
{
    return m_chatId.value();
}

void QTdChatTypeSecret::unmarshalJson(const QJsonObject &json)
{
    QTdChatTypePrivate::unmarshalJson(json);
    m_chatId = json["secret_chat_id"].toVariant().toLongLong();
    emit secretChatIdChanged();
}

QTdChatTypeSuperGroup::QTdChatTypeSuperGroup(QObject *parent)
    : QTdChatType(parent)
    , m_groupId(0)
    , m_isChannel(false)
{
    setType(CHAT_TYPE_SUPERGROUP);
}

QString QTdChatTypeSuperGroup::qmlSuperGroupId() const
{
    return m_groupId.toQmlValue();
}

qint64 QTdChatTypeSuperGroup::superGroupId() const
{
    return m_groupId.value();
}

bool QTdChatTypeSuperGroup::isChannel() const
{
    return m_isChannel;
}

void QTdChatTypeSuperGroup::unmarshalJson(const QJsonObject &json)
{
    QTdChatType::unmarshalJson(json);
    m_groupId = json["supergroup_id"];
    emit superGroupIdChanged();
    m_isChannel = json["is_channel"].toBool();
    emit isChannelChanged();
}
