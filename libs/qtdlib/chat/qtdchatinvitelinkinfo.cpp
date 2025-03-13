#include "qtdchatinvitelinkinfo.h"
#include "client/qtdclient.h"
#include "user/requests/qtdgetuserrequest.h"
#include "utils/await.h"
#include "user/qtdusers.h"
#include "common/qtdhelpers.h"

QTdChatInviteLinkInfo::QTdChatInviteLinkInfo(QObject *parent)
    : QTdObject(parent)
    , m_inviteLink("")
    , m_chatId(0)
    , m_type(new QTdChatType)
    , m_title("")
    , m_photo(new QTdChatPhoto)
    , m_memberCount(0)
    , m_highlightedMemberCount(0)
    , m_memberUsers(Q_NULLPTR)
{
    m_memberUsers.reset(new QQmlObjectListModel<QTdUser>(this));
}

QString QTdChatInviteLinkInfo::inviteLink() const
{
    return m_inviteLink;
}

qint64 QTdChatInviteLinkInfo::chatId() const
{
    return m_chatId.value();
}

QString QTdChatInviteLinkInfo::qmlChatId() const
{
    return m_chatId.toQmlValue();
}

QTdChatType *QTdChatInviteLinkInfo::type() const
{
    return m_type.data();
}

QString QTdChatInviteLinkInfo::title() const
{
    return m_title;
}

QTdChatPhoto *QTdChatInviteLinkInfo::photo() const
{
    return m_photo.data();
}

qint32 QTdChatInviteLinkInfo::memberCount() const
{
    return m_memberCount.value();
}

QString QTdChatInviteLinkInfo::qmlMemberCount() const
{
    return m_memberCount.toQmlValue();
}

QList<qint64> QTdChatInviteLinkInfo::memberUserIds() const
{
    return m_memberUserIds;
}
QString QTdChatInviteLinkInfo::highlightedMemberCount() const
{
    return m_highlightedMemberCount.toQmlValue();
}

QQmlObjectListModel<QTdUser> *QTdChatInviteLinkInfo::memberUsers() const
{
    return m_memberUsers.data();
}

bool QTdChatInviteLinkInfo::isPublic() const
{
    return m_isPublic;
}

QString QTdChatInviteLinkInfo::initials() const
{
    return m_initials;
}
QString QTdChatInviteLinkInfo::avatarColor() const
{
    return m_avatarColor;
}

void QTdChatInviteLinkInfo::unmarshalJson(QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_inviteLink = json["invite_link"].toString();
    m_chatId = json["chat_id"].toVariant().toLongLong();
    m_type->unmarshalJson(json["type"].toObject());
    m_title = json["title"].toString();
    m_photo->unmarshalJson(json["photo"].toObject());
    m_photo->small()->downloadFile();
    m_memberCount = json["member_count"].toInt();

    auto userIds = json["member_user_ids"].toArray();
    for (const QJsonValue &userId : userIds) {
        m_memberUserIds << userId.toVariant().toLongLong();
    }
    for (const qint64 &userId : m_memberUserIds) {
        QScopedPointer<QTdUser> user(QTdUsers::instance()->model()->getByUid(QString::number(userId)));
        if (user.isNull()) {
            QScopedPointer<QTdGetUserRequest> req(new QTdGetUserRequest);
            req->setUserId(userId);
            QFuture<QTdResponse> resp = req->sendAsync();
            await(resp);
            if (resp.result().isError()) {
                qWarning() << "Failed to get user with error: " << resp.result().errorString();
                return;
            }
            QScopedPointer<QTdUser> reqUser(new QTdUser);
            reqUser->unmarshalJson(resp.result().json());
            m_memberUsers->append(reqUser.take());
        } else {
            m_memberUsers->append(user.take());
        }
    }
    m_isPublic = json["is_public"].toBool();
    m_initials = QTdHelpers::initials(m_title);
    m_highlightedMemberCount = m_memberUserIds.count();
    qsrand(QTime::currentTime().msec());
    m_avatarColor = QTdHelpers::avatarColor(rand());
    emit chatInviteLinkInfoChanged();
}
