#include "utils/i18n.h"
#include "qtdchat.h"
#include <QDebug>
#include <QJsonArray>
#include "qtdchattypefactory.h"
#include "qtdchatactionfactory.h"
#include "client/qtdclient.h"
#include "qtdsecretchat.h"
#include "qtdchatlistmodel.h"
#include "chat/requests/qtdopenchatrequest.h"
#include "chat/requests/qtdclosechatrequest.h"
#include "chat/requests/qtdclosesecretchatrequest.h"
#include "chat/requests/qtdsetchattitlerequest.h"
#include "chat/requests/qtdsendchatactionrequest.h"
#include "chat/requests/qtddeletechathistoryrequest.h"
#include "chat/requests/qtdleavechatrequest.h"
#include "chat/requests/qtdclosesecretchatrequest.h"
#include "chat/requests/qtdsetchatnotificationsettings.h"
#include "user/qtdusers.h"
#include "common/qtdhelpers.h"
#include "messages/requests/qtdgetmessagerequest.h"
#include "utils/await.h"

QTdChat::QTdChat(QObject *parent)
    : QAbstractInt64Id(parent)
    , m_chatType(Q_NULLPTR)
    , m_chatActionBar(Q_NULLPTR)
    , m_chatPhoto(new QTdChatPhoto)
    , m_lastMessage(new QTdMessage)
    , m_position(new QTdChatPosition)
    , m_canBeReported(false)
    , m_unreadCount(0)
    , m_lastReadInboxMsg(0)
    , m_lastReadOutboxMsg(0)
    , m_unreadMentionCount(0)
    , m_notifySettings(new QTdNotificationSettings)
    , m_messages(0)
    , m_chatOpen(false)
    , m_draftMessage(new QTdDraftMessage)
{
    setType(CHAT);
    m_my_id = QTdClient::instance()->getOption("my_id").toLongLong();
    m_messages = new QQmlObjectListModel<QTdMessage>(this, "", "id");
    connect(QTdClient::instance(), &QTdClient::updateChatAction, this, &QTdChat::handleUpdateChatAction);
    connect(QTdClient::instance(), &QTdClient::updateChatActionBar, this, &QTdChat::handleUpdateChatActionBar);
    connect(m_lastMessage.data(), &QTdMessage::senderChanged, this, &QTdChat::summaryChanged);
    emit messagesChanged();
}

void QTdChat::unmarshalJson(const QJsonObject &json)
{
    QAbstractInt64Id::unmarshalJson(json);
    updateChatReadInbox(json);
    updateChatReadOutbox(json);
    updateChatTitle(json);

    m_chatType.reset(QTdChatFactory::createType(json["type"].toObject(), this));
    emit chatTypeChanged(m_chatType.data());

    updateChatActionBar(json["action_bar"].toObject());
    updateChatPosition(json);

    if (isSecret()) {
        auto c = static_cast<QTdSecretChat *>(this);
        c->getSecretChatData();
    }
    updateLastMessage(json["last_message"].toObject());

    m_canBeReported = json["can_be_reported"].toBool();
    emit canBeReportedChanged();
    updateChatUnreadMentionCount(json);
    updateChatReplyMarkup(json);
    updateChatDraftMessage(json["draft_message"].toObject());
    m_notifySettings->unmarshalJson(json["notification_settings"].toObject());
    emit notificationSettingsChanged();
    updateChatPhoto(json["photo"].toObject());
    onChatDeserialized();
}

QString QTdChat::title() const
{
    if (isMyself())
        return gettext("Saved Messages");
    else if (isPrivate() || isSecret()) {
        if (user()->isDeleted()) {
            return gettext("Deleted User");
        }
    }
    return m_title;
}

QTdMessage *QTdChat::lastMessage() const
{
    return m_lastMessage.data();
}

QTdChatPhoto *QTdChat::chatPhoto() const
{
    return m_chatPhoto.data();
}

QString QTdChat::initials() const
{
    return QTdHelpers::initials(m_title);
}

QString QTdChat::avatarColor(qint64 userId)
{
    return isMyself() ? QTdHelpers::selfColor() : QTdHelpers::avatarColor(userId);
}

void QTdChat::sendChatAction(bool isTyping)
{
    //TODO: Make more actions available
    QScopedPointer<QTdSendChatActionRequest> req(new QTdSendChatActionRequest);
    req->setChatId(id());
    QTdClient::instance()->send(req.data());
}

bool QTdChat::isMuted() const
{
    return m_notifySettings->muteFor() > 0;
}

bool QTdChat::isPrivate() const
{
    return qobject_cast<QTdChatTypePrivate *>(m_chatType.data()) != nullptr;
}

bool QTdChat::isSecret() const
{
    return qobject_cast<QTdChatTypeSecret *>(m_chatType.data()) != nullptr;
}

bool QTdChat::isGroup() const
{
    return isBasicGroup() || isSuperGroup();
}

bool QTdChat::isBasicGroup() const
{
    return qobject_cast<QTdChatTypeBasicGroup *>(m_chatType.data()) != nullptr;
}

bool QTdChat::isSuperGroup() const
{
    auto result = qobject_cast<QTdChatTypeSuperGroup *>(m_chatType.data());
    return result != nullptr && !result->isChannel();
}

bool QTdChat::isChannel() const
{
    auto result = qobject_cast<QTdChatTypeSuperGroup *>(m_chatType.data());
    return result != nullptr && result->isChannel();
}

bool QTdChat::isMyself() const
{
    return id() == m_my_id;
}

bool QTdChat::isWritable() const
{
    return true;
}

bool QTdChat::isOpen() const
{
    return m_chatOpen;
}

bool QTdChat::isPinned() const
{
    return m_position->isPinned();
}

bool QTdChat::isBot() const {
    if (isPrivate()) {
        auto userChatType = qobject_cast<QTdChatTypePrivate *>(m_chatType.data());
        if (userChatType->user()->isBot()) {
            return true;
        }
    }
    return false;
}

bool QTdChat::canBeReported() const
{
    return m_canBeReported;
}

bool QTdChat::hasUnreadMessages() const
{
    return unreadCount() > 0;
}

QString QTdChat::qmlUnreadCount() const
{
    return m_unreadCount.toQmlValue();
}

qint32 QTdChat::unreadCount() const
{
    return m_unreadCount.value();
}

QString QTdChat::qmlLastReadInboxMessageId() const
{
    return m_lastReadInboxMsg.toQmlValue();
}

qint64 QTdChat::lastReadInboxMessageId() const
{
    return m_lastReadInboxMsg.value();
}

QString QTdChat::qmlLastReadOutboxMessageId() const
{
    return m_lastReadOutboxMsg.toQmlValue();
}

qint64 QTdChat::lastReadOutboxMessageId() const
{
    return m_lastReadOutboxMsg.value();
}

bool QTdChat::hasUnreadMentions() const
{
    return unreadMentionCount() > 0;
}

QString QTdChat::qmlUnreadMentionCount() const
{
    return m_unreadMentionCount.toQmlValue();
}

qint32 QTdChat::unreadMentionCount() const
{
    return m_unreadMentionCount.value();
}

QString QTdChat::qmlOnlineMemberCount() const
{
    return m_onlineMemberCount.toQmlValue();
}

qint32 QTdChat::onlineMemberCount() const
{
    return m_onlineMemberCount.value();
}

QString QTdChat::qmlReplyMarkupMessageId() const
{
    return m_replyMarkupMessageId.toQmlValue();
}

qint64 QTdChat::replyMarkupMessageId() const
{
    return m_replyMarkupMessageId.value();
}

QTdMessage *QTdChat::replyMarkupMessage() const
{
    return m_replyMarkupMessage.data();
}

bool QTdChat::hasReplyMarkup() const
{
    return m_replyMarkupMessageId.value() != 0;
}

void QTdChat::loadReplyMarkupMessage()
{
    if (!hasReplyMarkup()) {
        return;
    }
    QScopedPointer<QTdGetMessageRequest> req(new QTdGetMessageRequest);
    req->setChatId(id());
    req->setMessageId(m_replyMarkupMessageId.value());
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Failed to get reply markup message with error: " << resp.result().errorString();
        return;
    }
    m_replyMarkupMessage.reset(new QTdMessage(this));
    m_replyMarkupMessage->unmarshalJson(resp.result().json());
    emit replyMarkupMessageChanged();
}

QTdNotificationSettings *QTdChat::notificationSettings() const
{
    return m_notifySettings.data();
}
QTdChatPosition *QTdChat::position() const
{
    return m_position.data();
}

QString QTdChat::action() const
{
    auto *users = QTdUsers::instance()->model();
    QString actionMessage;
    switch (m_chatActions.count()) {
    case 0:
        return "";
    case 1: {
        auto *user = users->getByUid(QString::number(m_chatActions.first().userId.value()));

        if (user) {
            if (m_chatActions.first().isPersonal)
                actionMessage = m_chatActions.first().personal_description;
            else
                actionMessage = QString("%1 %2 ").arg(user->firstName(), m_chatActions.first().singular_description);
        }
    } break;
    case 2: {
        auto *user1 = users->getByUid(
                QString::number(m_chatActions.first().userId.value()));

        auto *user2 = users->getByUid(
                QString::number(m_chatActions.last().userId.value()));

        if (user1 && user2)
            actionMessage = QString("%1, %2 %3").arg( 
                    user1->firstName(), user2->firstName(), m_chatActions.last().plural_description);
    } break;
    default: {
        actionMessage = QString("%1 %2").arg(
                                                m_chatActions.count())
                                .arg(m_chatActions.first().plural_description);
    }
    }
    return actionMessage;
}

QTdUser *QTdChat::user() const {
    if (isPrivate() || isSecret()) {
        auto userChatType = qobject_cast<QTdChatTypePrivate *>(m_chatType.data());
        return userChatType->user();
    }
    return Q_NULLPTR;
}

QVariant QTdChat::summary()
{
    QVariantList summary;
    if (draftMessage()->inputMessageText()->text() != "" || draftMessage()->replyToMessageId() != 0) {
        summary.insert(0, QString(gettext("Draft:")));
        summary.insert(1, draftMessage()->inputMessageText()->text());
    } else {
        summary.insert(0, QString());
        if (action() != "") {
            summary.insert(1, action());
        } else if (!m_lastMessage->isValid()) {
            summary.insert(1, QString());
        } else if ((isPrivate() || isSecret()) && !m_lastMessage->isOutgoing()) {
            summary.insert(1, m_lastMessage->summary());
        } else if (!m_lastMessage->sender()->displayName().isEmpty()) {
            summary.insert(1, QString("%1: %2").arg(m_lastMessage->isOutgoing() ? gettext("Me") : m_lastMessage->sender()->displayName(), m_lastMessage->summary()));
        } else {
            summary.insert(1, m_lastMessage->summary());
        }
    }
    return QVariant::fromValue(summary);
}

QObject *QTdChat::messages() const
{
    return m_messages;
}

void QTdChat::openChat()
{
    m_chatOpen = true;
    emit isOpenChanged();
    QScopedPointer<QTdOpenChatRequest> req(new QTdOpenChatRequest);
    req->setChatId(id());
    QTdClient::instance()->send(req.data());
    onChatOpened();
    QTdChat::loadReplyMarkupMessage();
}

void QTdChat::closeChat()
{
    m_chatOpen = false;
    QScopedPointer<QTdCloseChatRequest> req(new QTdCloseChatRequest);
    req->setChatId(id());
    QTdClient::instance()->send(req.data());
    m_currentMessageIndex = -1;
    emit closed();
    emit isOpenChanged();
}

void QTdChat::setTitle(const QString &title)
{
    if (m_title != title) {
        QScopedPointer<QTdSetChatTitleRequest> req(new QTdSetChatTitleRequest);
        req->setTitle(id(), title);
        QTdClient::instance()->send(req.data());
    }
}

void QTdChat::deleteChatHistory(const bool &removeFromChatlist, const bool &forAllUsers)
{
    if (m_chatType->type() == QTdChat::CHAT_TYPE_SUPERGROUP || isChannel()) {
        qWarning() << "Cannot delete chat history for supergroups or channels";
        return;
    }
    if (isSecret()) {
        auto secretChatType = qobject_cast<QTdChatTypeSecret *>(m_chatType.data());
        QScopedPointer<QTdCloseSecretChatRequest>
                req(new QTdCloseSecretChatRequest);
        req->setSecretChatId(secretChatType->secretChatId());
        QTdClient::instance()->send(req.data());
    }
    QScopedPointer<QTdDeleteChatHistoryRequest> req(new QTdDeleteChatHistoryRequest);
    req->setChatId(id());
    req->setRemoveFromChatList(removeFromChatlist);
    req->setRevoke(forAllUsers);
    QTdClient::instance()->send(req.data());
}

void QTdChat::leaveSecretChat() {
    if (m_chatType->type() == QTdChat::CHAT_TYPE_SECRET) {
        QScopedPointer<QTdCloseSecretChatRequest> req(new QTdCloseSecretChatRequest);
        auto c = static_cast<QTdSecretChat *>(this);
        req->setSecretChatId(c->secretChatId());
        QTdClient::instance()->send(req.data());
    }
}

void QTdChat::leaveChat()
{
    /**
     * Because telegram likes to have all different types of
     * groups and it is probably going to change again. SO let's
     * for the sake of simplicity use a switch and handle each type
     * appropriately.
     *
     * Currently private & secret chats can only delete history and be removed
     * from chatlist.
     *
     * Supergroups and basicgroups can be left using the id()
     * Strangely it takes the id and not superGroupId and basicGroupId
     */
    QScopedPointer<QTdLeaveChatRequest> req(new QTdLeaveChatRequest);
    switch (m_chatType->type()) {
    case QTdChat::CHAT_TYPE_PRIVATE:
        return deleteChatHistory(true);
    case QTdChat::CHAT_TYPE_SECRET: {
        leaveSecretChat();
        return deleteChatHistory(true);
    }
    case QTdChat::CHAT_TYPE_SUPERGROUP:
    case QTdChat::CHAT_TYPE_BASIC_GROUP: {
        req->setChatId(id());
        break;
    }
    default:
        break;
    }
    QTdClient::instance()->send(req.data());
    QTdChatListModel::instance()->model()->remove(this);
}

void QTdChat::updateChatReadInbox(const QJsonObject &json)
{
    m_lastReadInboxMsg = json["last_read_inbox_message_id"].toVariant().toLongLong();
    emit lastReadInboxMessageIdChanged();
    m_unreadCount = json["unread_count"].toInt();
    emit unreadCountChanged();
    QTdClient::instance()->setUnreadMapEntry(id(), unreadCount());
}

void QTdChat::updateChatReadOutbox(const QJsonObject &json)
{
    m_lastReadOutboxMsg = json["last_read_outbox_message_id"].toVariant().toLongLong();
    emit lastReadOutboxMessageIdChanged();
}

void QTdChat::updateNonFilterChatListPosition(const QJsonObject &new_position)
{
    auto chatList = new_position["list"].toObject();
    if (!chatList.isEmpty() && chatList["@type"].toString() != "chatListFilter") {
        m_position->unmarshalJson(new_position);
        emit positionChanged();
        emit isPinnedChanged();
    }
}

void QTdChat::updateChatPosition(const QJsonObject &json)
{
    auto new_position = json["position"].toObject();
    if (!new_position.isEmpty()) {
        updateNonFilterChatListPosition(new_position);
    }
}

void QTdChat::updateChatPositions(const QJsonObject &json)
{
    auto positions = json["positions"].toArray();
    for (auto position : positions) {
        // TODO: re: #258.2 - handle multiple chat lists
        updateNonFilterChatListPosition(position.toObject());
    }
}

void QTdChat::updateChatPhoto(const QJsonObject &photo)
{
    m_chatPhoto->unmarshalJson(photo);
    emit chatPhotoChanged(m_chatPhoto.data());

    if (m_chatPhoto->small()->local()->path().isEmpty()) {
        connect(m_chatPhoto->small()->local(), &QTdLocalFile::pathChanged, this, &QTdChat::handleChatPhotoDownloaded);
        m_chatPhoto->small()->downloadFile();
    } else {
        QTdClient::instance()->setAvatarMapEntry(id(), m_chatPhoto->small()->local()->path());
    }
}

void QTdChat::updateChatReplyMarkup(const QJsonObject &json)
{
    m_replyMarkupMessageId = json["reply_markup_message_id"];
    if (hasReplyMarkup() && m_chatOpen) {
        loadReplyMarkupMessage();
    }
}

void QTdChat::updateChatDraftMessage(const QJsonObject &json)
{
    if (json.isEmpty()) {
        m_draftMessage.reset(new QTdDraftMessage);
    } else {
        m_draftMessage->unmarshalJson(json);
    }
    emit summaryChanged();
    emit draftMessageChanged();
}

void QTdChat::updateChatTitle(const QJsonObject &json)
{
    m_title = json["title"].toString();
    emit titleChanged(m_title);
}

void QTdChat::updateChatUnreadMentionCount(const QJsonObject &json)
{
    m_unreadMentionCount = json["unread_mention_count"];
    emit unreadMentionCountChanged();
}

void QTdChat::updateChatOnlineMemberCount(const QJsonObject &json)
{
    m_onlineMemberCount = json["online_member_count"];
    emit onlineMemberCountChanged();
}

void QTdChat::updateChatNotificationSettings(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    m_notifySettings->unmarshalJson(json["notification_settings"].toObject());
    emit notificationSettingsChanged();
}

void QTdChat::updateLastMessage(const QJsonObject &json)
{
    if (json.isEmpty()) {
        m_lastMessage.reset(new QTdMessage);
    } else {
        m_lastMessage->unmarshalJson(json);
    }
    emit lastMessageChanged(m_lastMessage.data());
    emit summaryChanged();
}

void QTdChat::handleUpdateChatAction(const QJsonObject &json)
{
    const qint64 cid = json["chat_id"].toVariant().toLongLong();
    if (cid != id()) {
        return;
    }
    updateChatAction(json);
}

void QTdChat::handleUpdateChatActionBar(const QJsonObject &json)
{
    const qint64 cid = json["chat_id"].toVariant().toLongLong();
    if (cid != id()) {
        return;
    }
    updateChatActionBar(json["action_bar"].toObject());
}

void QTdChat::handleChatPhotoDownloaded()
{
    QTdClient::instance()->setAvatarMapEntry(id(), m_chatPhoto->small()->local()->path());
}

void QTdChat::onChatOpened() {

}

void QTdChat::onChatClosed()
{
}

void QTdChat::onChatDeserialized()
{
}

void QTdChat::forwardMessage(const QString &messageId)
{
    QStringList forwardingMessages = QStringList(messageId);
    emit forwardingMessagesAction(forwardingMessages, this);
}

void QTdChat::mute(const qint32 &duration) {
    QScopedPointer<QTdSetChatNotificationSettings> req(new QTdSetChatNotificationSettings);
    req->setNotificationSettings(m_notifySettings.data());
    req->setChatId(id());
    m_notifySettings->setMuteFor(duration);
    m_notifySettings->setUseDefaultMuteFor(false);
    QTdClient::instance()->send(req.data());
}

void QTdChat::updateChatAction(const QJsonObject &json)
{
    const qint64 user_id = json["sender_id"].toObject()["user_id"].toVariant().toLongLong();
    const QJsonObject data = json["action"].toObject();
    QTdChatAction *action = QTdChatActionFactory::create(data, this);
    if (action->type() == QTdChatAction::Type::CHAT_ACTION_CANCEL && m_chatActions.contains(user_id)) {
        m_chatActions.remove(user_id);
    } else if (action->type() != QTdChatAction::Type::CHAT_ACTION_CANCEL && !m_chatActions.contains(user_id)) {
        m_chatActions.insert(user_id, useraction(user_id, user_id == id(), action->personal_description(), action->singular_description(),
                                                 action->plural_description()));
    }
    action->deleteLater();
    emit summaryChanged();
}

void QTdChat::updateChatActionBar(const QJsonObject &json)
{
    m_chatActionBar.reset(QTdChatActionBarFactory::create(json, this));
    emit chatActionBarChanged();
}

QTdChatType *QTdChat::chatType() const
{
    return m_chatType.data();
}

QTdChatPhoto::QTdChatPhoto(QObject *parent)
    : QTdPhoto(parent)
{
    setType(CHAT_PHOTO);
}

QString QTdChat::formatDate(const QDateTime &dt)
{
    return QTdHelpers::formatDate(dt);
}

int QTdChat::currentMessageIndex() const
{
    return m_currentMessageIndex;
}

void QTdChat::positionMessageListViewAtIndex(int index)
{
    m_currentMessageIndex = index;
    emit currentMessageIndexChanged();
}

QTdDraftMessage *QTdChat::draftMessage() const
{
    return m_draftMessage.data();
}

QString QTdChat::smallPhotoPath() const
{
    if (isPrivate() || isSecret() ) {
        auto userChatType = qobject_cast<QTdChatTypePrivate *>(m_chatType.data());
        if (userChatType->user()->isDeleted()) {
            return "image://theme/account";
        }
    }
    return m_chatPhoto->smallPhotoPath();
}

bool QTdChat::hasChatActionBar() const {
    return !m_chatActionBar.isNull();
}

QTdChatActionBar *QTdChat::chatActionBar() const {
    return m_chatActionBar.data();
}
