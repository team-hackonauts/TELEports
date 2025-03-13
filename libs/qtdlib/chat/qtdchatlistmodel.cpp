#include "qtdchatlistmodel.h"
#include <QScopedPointer>
#include <QList>
#include <QVariant>
#include "client/qtdclient.h"
#include "chat/requests/qtdloadchatsrequest.h"
#include "chat/requests/qtdcreatenewsecretchatrequest.h"
#include "chat/requests/qtdcreateprivatechatrequest.h"
#include "chat/requests/qtdgetchatrequest.h"
#include "chat/requests/qtdsetpinnedchatsrequest.h"
#include "chat/requests/qtdleavechatrequest.h"
#include "chat/requests/qtdforwardmessagesrequest.h"
#include "chat/requests/qtdsetchatdraftrequest.h"
#include "chat/requests/qtdsearchpublicchatrequest.h"
#include "chat/requests/qtdjoinchatrequest.h"
#include "chat/requests/qtdcheckchatinvitelinkrequest.h"
#include "chat/requests/qtdjoinchatbyinvitelinkrequest.h"
#include "chat/requests/qtdsetchatmessagettlrequest.h"
#include "messages/requests/qtdsendmessagerequest.h"
#include "messages/requests/qtdopenmessagecontentrequest.h"
#include "messages/requests/qtdsetpollanswerrequest.h"
#include "messages/requests/content/qtdinputmessagetext.h"
#include "common/qtdhelpers.h"

#include "utils/await.h"
#include "utils/i18n.h"
#include "chat/qtdchattypefactory.h"
#include "qtdsecretchat.h"

QPointer<QTdChatListModel> QTdChatListModel::s_chatlistmodel;

QTdChatListModel::QTdChatListModel(QObject *parent)
    : QObject(parent)
    , m_model(Q_NULLPTR)
    , m_currentChat(Q_NULLPTR)
    , m_forwardedFromChat(Q_NULLPTR)
    , m_forwardingMessages(QStringList())
    , m_listMode(ListMode::Idle)
    , m_positionWaitTimer(new QTimer(this))
    , m_chatToOpenOnUpdate(0)
{
    if (s_chatlistmodel.isNull()) {
        s_chatlistmodel = this;
    }

    m_model = new QQmlObjectListModel<QTdChat>(this, "", "id");
    m_positionWaitTimer->setInterval(180000);
    m_positionWaitTimer->setSingleShot(true);
    connect(this->m_positionWaitTimer, &QTimer::timeout, this, &QTdChatListModel::onPositionInfoTimeout);

    connect(QTdClient::instance(), &QTdClient::chats, this, &QTdChatListModel::handleChats);
    connect(QTdClient::instance(), &QTdClient::chat, this, &QTdChatListModel::handleChat);
    connect(QTdClient::instance(), &QTdClient::updateNewChat, this, &QTdChatListModel::handleUpdateNewChat);
    connect(QTdClient::instance(), &QTdClient::authStateChanged, this, &QTdChatListModel::handleAuthStateChanges);
    connect(QTdClient::instance(), &QTdClient::updateChatPosition, this, &QTdChatListModel::handleUpdateChatPosition);
    connect(QTdClient::instance(), &QTdClient::updateChatLastMessage, this, &QTdChatListModel::handleUpdateChatLastMessage);
    connect(QTdClient::instance(), &QTdClient::updateChatReadInbox, this, &QTdChatListModel::updateChatReadInbox);
    connect(QTdClient::instance(), &QTdClient::updateChatReadOutbox, this, &QTdChatListModel::updateChatReadOutbox);
    connect(QTdClient::instance(), &QTdClient::updateChatPhoto, this, &QTdChatListModel::handleUpdateChatPhoto);
    connect(QTdClient::instance(), &QTdClient::updateChatReplyMarkup, this, &QTdChatListModel::handleUpdateChatReplyMarkup);
    connect(QTdClient::instance(), &QTdClient::updateChatDraftMessage, this, &QTdChatListModel::handleUpdateChatDraftMessage);
    connect(QTdClient::instance(), &QTdClient::updateChatTitle, this, &QTdChatListModel::handleUpdateChatTitle);
    connect(QTdClient::instance(), &QTdClient::updateChatUnreadMentionCount, this, &QTdChatListModel::handleUpdateChatUnreadMentionCount);
    connect(QTdClient::instance(), &QTdClient::updateChatNotificationSettings, this, &QTdChatListModel::handleUpdateChatNotificationSettings);
    connect(QTdClient::instance(), &QTdClient::updateChatOnlineMemberCount, this, &QTdChatListModel::handleUpdateChatOnlineMemberCount);
}

QTdChatListModel *QTdChatListModel::instance()
{
    return s_chatlistmodel;
}

QQmlObjectListModel<QTdChat> *QTdChatListModel::model() const
{
    return m_model;
}

QTdChat *QTdChatListModel::currentChat() const
{
    return m_currentChat;
}

QTdChat *QTdChatListModel::chatById(const qint64 &chatId) const
{
    return m_model->getByUid(QString::number(chatId));
}

void QTdChatListModel::createOrOpenSecretChat(const qint64 &userId)
{
    qint64 chatId = 0;
    foreach (QTdChat *chat, m_model->toList()) {
        if (chat->isSecret()) {
            auto c = static_cast<QTdSecretChat *>(chat);
            if (!c->isClosed() && c->userId() == userId) {
                chatId = c->id();
                break;
            }
        }
    }
    if (chatId == 0) {
        QScopedPointer<QTdCreateNewSecretChatRequest> req(new QTdCreateNewSecretChatRequest);
        req->setUserId(userId);
        QFuture<QTdResponse> resp = req->sendAsync();
        await(resp);
        if (resp.result().isError()) {
            qWarning() << "Error during secret chat creation:" << resp.result().errorString();
            return;
        }
        chatId = resp.result().json()["id"].toVariant().toLongLong();
        if (chatId == 0) {
            return;
        }
    }
    setCurrentChatById(chatId);
}

void QTdChatListModel::createOrOpenPrivateChat(const qint64 &userId)
{
    QScopedPointer<QTdCreatePrivateChatRequest> req(new QTdCreatePrivateChatRequest);
    req->setUserId(userId);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during private chat creation:" << resp.result().errorString();
        return;
    }
    qint64 chatId = resp.result().json()["id"].toVariant().toLongLong();
    setCurrentChatById(chatId);
}

void QTdChatListModel::createOrOpenSavedMessages() {
    createOrOpenPrivateChat(QTdClient::instance()->getOption("my_id").toLongLong());
}

void QTdChatListModel::setCurrentChatById(const qint64 &chatId)
{
    QTdChat *currentChat = chatById(chatId);
    setCurrentChat(currentChat);
}

void QTdChatListModel::setCurrentChatByUsername(const QString &username)
{
    qDebug() << "OPENING CHAT" << username;
    QScopedPointer<QTdSearchPublicChatRequest> req(new QTdSearchPublicChatRequest);
    req->setChatUsername(username);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during public chat search:" << resp.result().errorString();
        if (resp.result().errorCode() == 400)
            emit invalidChatUsername(username);
        return;
    }
    qint64 chatId = resp.result().json()["id"].toVariant().toLongLong();
    setCurrentChatById(chatId);
}

qint64 QTdChatListModel::chatIdByUsername(const QString &username)
{
    QScopedPointer<QTdSearchPublicChatRequest> req(new QTdSearchPublicChatRequest);
    req->setChatUsername(username);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during public chat search:" << resp.result().errorString();
        return -1;
    }
    return resp.result().json()["id"].toVariant().toLongLong();
}

qint32 QTdChatListModel::forwardingMessagesCount() const
{
    return m_forwardingMessages.length();
}

void QTdChatListModel::setCurrentChat(QTdChat *currentChat)
{
    if (currentChat == nullptr) {
        return;
    }
    if (m_currentChat && m_currentChat->isOpen()) {
        if (m_currentChat == currentChat)
            return;
        else
            m_currentChat->closeChat();
    }

    m_currentChat = currentChat;
    emit currentChatChanged();
}

QTdChat *QTdChatListModel::forwardedFromChat() const
{
    return m_forwardedFromChat;
}

void QTdChatListModel::setForwardedFromChat(QTdChat *forwardedFromChat)
{
    if (m_forwardedFromChat == forwardedFromChat)
        return;
    m_forwardedFromChat = forwardedFromChat;
}

QStringList QTdChatListModel::forwardingMessages() const
{
    return m_forwardingMessages;
}

void QTdChatListModel::setForwardingMessages(QStringList forwardingMessages)
{
    if (m_forwardingMessages == forwardingMessages)
        return;
    m_forwardingMessages = forwardingMessages;
}

void QTdChatListModel::handleChat(const QJsonObject &data)
{
    QScopedPointer<QTdChat> chat(new QTdChat);
    chat->unmarshalJson(data);
    handleUpdateNewChat(data);
}

void QTdChatListModel::handleChats(const QJsonObject &data)
{
    QJsonArray chats = data["chat_ids"].toArray();
    if (chats.count() == 0) {
        qDebug() << "No more chats found, completing initial load.";
        m_receivedChatIds.clear();
        return;
    }
    qDebug() << "Received" << chats.count() << "chats";
    foreach (QJsonValue chat, chats) {
        auto chatId = chat.toVariant().toLongLong();
        if (chatId == 0) {
            continue;
        }
        m_receivedChatIds.append(chatId);
        //Only request chats that we did not receive already
        if (!chatById(chatId)) {
            QScopedPointer<QTdGetChatRequest> chatReq(new QTdGetChatRequest);
            chatReq->setChatId(chatId);
            qDebug() << "Request chat id" << chatId << "to be added to chatmodel";
            chatReq->sendAsync();
        } else {
            qDebug() << "Chat" << chatId << "already received, ignoring";
        }
    }
    emit modelPopulatedCompleted();
}

void QTdChatListModel::handleUpdateNewChat(const QJsonObject &data)
{
    const qint64 id = data["id"].toVariant().toLongLong();
    // Need to remember the model actually indexes on the qmlId variant which is a QString
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->unmarshalJson(data);
    } else {
        tdchat = QTdChatFactory::createChat(data["type"].toObject());
        tdchat->unmarshalJson(data);
        m_model->append(tdchat);
        connect(tdchat, &QTdChat::chatStatusChanged, this, &QTdChatListModel::chatStatusChanged);
        connect(tdchat, &QTdChat::forwardingMessagesAction, this, &QTdChatListModel::handleForwardingMessagesAction);
        emit chatCreated(tdchat->id());
    }
    emit contentsChanged();
    if (m_chatToOpenOnUpdate == tdchat->id()) {
        qDebug() << "Auto-opening chat" << tdchat->id();
        setCurrentChat(tdchat);
        m_chatToOpenOnUpdate = 0;
    }
}

void QTdChatListModel::handleUpdateChatPosition(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatPosition(data);
        // We also need to update the internal pinned chats list now
        // otherwise any pinned chats will get removed when togglePinChat() is called
        auto position = data["position"].toObject();
        if (!position.isEmpty() && position["list"].toObject()["@type"].toString() != "chatListFilter") {
            long long order = position["order"].toVariant().toLongLong();
            PinnedChat pinnedChat(id, order);
            if (position["is_pinned"].toVariant().toBool()) {
                if (!m_pinnedChats.contains(pinnedChat)) {
                    m_pinnedChats.append(pinnedChat);
                    std::sort(m_pinnedChats.begin(), m_pinnedChats.end());
                }
            } else {
                m_pinnedChats.removeAll(pinnedChat);
            }
        }
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatLastMessage(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateLastMessage(data["last_message"].toObject());
        tdchat->updateChatPositions(data);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleAuthStateChanges(const QTdAuthState *state)
{
    switch (state->type()) {
        case QTdAuthState::Type::AUTHORIZATION_STATE_CLOSED: {
            m_model->clear();
            break;
        }
    }
}

void QTdChatListModel::updateChatReadInbox(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatReadInbox(data);
        emit contentsChanged();
    }
}

void QTdChatListModel::updateChatReadOutbox(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatReadOutbox(data);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatPhoto(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatPhoto(data["photo"].toObject());
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatReplyMarkup(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatReplyMarkup(data);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatDraftMessage(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatDraftMessage(data["draft_message"].toObject());
        tdchat->updateChatPositions(data);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatTitle(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatTitle(data);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatUnreadMentionCount(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatUnreadMentionCount(data);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatNotificationSettings(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatNotificationSettings(data);
        emit contentsChanged();
    }
}

void QTdChatListModel::handleUpdateChatOnlineMemberCount(const QJsonObject &data)
{
    const qint64 id = data["chat_id"].toVariant().toLongLong();
    QTdChat *tdchat = chatById(id);
    if (tdchat) {
        tdchat->updateChatOnlineMemberCount(data);
        emit contentsChanged();
    }
}

void QTdChatListModel::sendForwardMessage(const QStringList &forwardMessageIds,
                                          const qint64 &recievingChatId,
                                          const qint64 &fromChatId,
                                          const QString &message)
{

    QString plainText;
    QJsonArray formatEntities = QTdHelpers::formatPlainTextMessage(message, plainText);
    QTdInputMessageText *messageText = new QTdInputMessageText();
    messageText->setText(message);
    messageText->setEntities(formatEntities);
    QScopedPointer<QTdForwardMessagesRequest> request(new QTdForwardMessagesRequest);
    request->setChatId(recievingChatId);
    request->setFromChatId(fromChatId);
    QScopedPointer<QTdSendMessageRequest> additionalTextMessagerequest(new QTdSendMessageRequest);
    additionalTextMessagerequest->setChatId(recievingChatId);
    additionalTextMessagerequest->setContent(messageText);
    QList<qint64> forwardingMessageIntIds;
    foreach (QString msgId, forwardMessageIds) {
        forwardingMessageIntIds.append(msgId.toLongLong());
    }
    request->setMessageIds(forwardingMessageIntIds);
    QTdClient::instance()->send(request.data());
    if (message != "") {
        QTdClient::instance()->send(additionalTextMessagerequest.data());
    }
}

void QTdChatListModel::togglePinChat(const qint64 &chatId, const bool &pinned)
{
    qlonglong maxPinnableChats = QTdClient::instance()->getOption("pinned_chat_count_max").toLongLong();
    if (pinned && m_pinnedChats.size() == maxPinnableChats) {
        emit showNotification(gettext("Maximum number of pinned chat exceeded"));
        return;
    }
    // Copy the internal list as we will wait for the updateChatPosition events
    // to update m_pinnedChats. This prevents us from prematurely updating and
    // having to handle errors when updating the pinned chats list.
    QList<qint64> chats;
    for (int i = 0; i < m_pinnedChats.size(); ++i) {
        chats.append(m_pinnedChats.at(i).id());
    }

    if (pinned && !chats.contains(chatId)) {
        chats.prepend(chatId);
    } else if (!pinned && chats.contains(chatId)) {
        chats.removeAll(chatId);
    }
    QScopedPointer<QTdSetPinnedChatsRequest> req(new QTdSetPinnedChatsRequest);
    req->setPinnedChats(chats);
    QTdClient::instance()->send(req.data());
}

void QTdChatListModel::handleForwardingMessagesAction()
{
    setListMode(ListMode::ForwardingMessages);
}

QTdChatListModel::ListMode QTdChatListModel::listMode() const
{
    return m_listMode;
}

void QTdChatListModel::setListMode(ListMode listMode)
{
    m_listMode = listMode;
    emit listModeChanged();
}

void QTdChatListModel::requestPositionInfo()
{
    if (!m_positionInfoSource) {
        m_positionInfoSource = QGeoPositionInfoSource::createDefaultSource(this);
        if (!m_positionInfoSource) {
            qWarning() << "Could not initialize position info source!";
            return;
        }
    }
    connect(m_positionInfoSource, &QGeoPositionInfoSource::positionUpdated,
            this, &QTdChatListModel::positionUpdated);
    m_positionInfoSource->requestUpdate(180000);
    m_positionWaitTimer->start();
}

void QTdChatListModel::cancelPositionInfo()
{
    disconnect(m_positionInfoSource, &QGeoPositionInfoSource::positionUpdated,
               this, &QTdChatListModel::positionUpdated);
    m_positionWaitTimer->stop();
}

void QTdChatListModel::onPositionInfoTimeout()
{
    cancelPositionInfo();
    emit positionInfoTimeout();
}

void QTdChatListModel::positionUpdated(const QGeoPositionInfo &positionInfo)
{
    cancelPositionInfo();
    emit positionInfoReceived(positionInfo.coordinate().latitude(), positionInfo.coordinate().longitude());
}

void QTdChatListModel::setChatDraftMessage(const QString &draftText,
                                           const qint64 &replyToMessageId,
                                           const qint64 &chatId)
{
    QScopedPointer<QTdInputMessageText> messageText(new QTdInputMessageText);
    messageText->setText(draftText);
    messageText->setClearDraft(false);
    QScopedPointer<QTdDraftMessage> draftMessage(new QTdDraftMessage);
    draftMessage->setInputMessageText(messageText.take());
    draftMessage->setReplyToMessageId(replyToMessageId);
    QScopedPointer<QTdSetChatDraftRequest> request(new QTdSetChatDraftRequest);
    request->setChatId(chatId);
    request->setDraftMessage(draftMessage.take());
    QTdClient::instance()->send(request.data());
}

void QTdChatListModel::joinChat(const qint64 &chatId) const
{
    QScopedPointer<QTdJoinChatRequest> req(new QTdJoinChatRequest);
    req->setChatId(chatId);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    qDebug() << resp.result().json();
    if (resp.result().isError()) {
        qWarning() << "Error during chat joining:" << resp.result().errorString();
    }
}

void QTdChatListModel::setChatToOpenOnUpdate(const qint64 &chatId)
{
    m_chatToOpenOnUpdate = chatId;
}

void QTdChatListModel::loadMoreChats(const QString &chatList) {
    QScopedPointer<QTdLoadChatsRequest> req(new QTdLoadChatsRequest);

    if (m_model->isEmpty()) {
        req->setChatList(chatList);
    }
    req->setLimit(10);
    req->sendAsync();
}

void QTdChatListModel::checkChatInviteLink(const QString &inviteLink)
{
    QScopedPointer<QTdCheckChatInviteLinkRequest> req(new QTdCheckChatInviteLinkRequest);
    req->setInviteLink(inviteLink);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during checking invite link:" << resp.result().errorString();
    }
    QPointer<QTdChatInviteLinkInfo> info(new QTdChatInviteLinkInfo);
    QJsonObject json = resp.result().json();
    info->unmarshalJson(json);
    if (info->chatId() != 0) {
        setCurrentChatById(info->chatId());
    } else {
        emit showChatInviteLinkInfo(info, inviteLink);
    }
}

void QTdChatListModel::joinChatByInviteLink(const QString &inviteLink)
{
    qDebug() << inviteLink;
    QScopedPointer<QTdJoinChatByInviteLinkRequest> req(new QTdJoinChatByInviteLinkRequest);
    req->setInviteLink(inviteLink);
    QFuture<QTdResponse> resp = req->sendAsync();
    await(resp);
    qDebug() << resp.result().json();
    if (resp.result().isError()) {
        qWarning() << "Error during joining chat by invite link:" << resp.result().errorString();
    }
    QScopedPointer<QTdChat> chat(new QTdChat);
    QJsonObject json = resp.result().json();
    chat->unmarshalJson(json);
    setChatToOpenOnUpdate(chat->id());
    setCurrentChatById(chat->id());
}

void QTdChatListModel::openMessageContent(const QString chatId, const QString messageId)
{
    QScopedPointer<QTdOpenMessageContentRequest> req(new QTdOpenMessageContentRequest);
    req->setChatId(chatId);
    req->setMessageId(messageId);
    QFuture<QTdResponse> resp = req->sendAsync();
}

void QTdChatListModel::sendSetTTL(const QString &chatId, const int &ttl)
{
    QScopedPointer<QTdSetChatMessageTtlRequest> req(new QTdSetChatMessageTtlRequest);
    req->setChatId(chatId.toLong());
    req->setTTL(ttl);
    QTdClient::instance()->send(req.data());
}

/**
 * @brief Set the answer (chosen option(s)) for a poll 
 */
void QTdChatListModel::setPollAnswer(const QString &chatId, const QString &messageId, const QVariantList &optionIds) {
    QScopedPointer<QTdSetPollAnswerRequest> req(new QTdSetPollAnswerRequest);
    QList<qint32> targetList;
    foreach(QVariant v, optionIds) {
        targetList << v.value<qint32>();
    }
    req->setChatId(chatId.toLong());
    req->setMessageId(messageId.toLong());
    req->setPollOptions(targetList);
    QTdClient::instance()->send(req.data());
}
