#include "qtdmessagelistmodel.h"
#include <QDebug>
#include <QJsonArray>
#include <QScopedPointer>
#include <QtPositioning/QGeoCoordinate>
#include <QTimer>
#include <QAudioRecorder>
#include "client/qtdclient.h"
#include "requests/qtdinputmessagecontentattachmentcaption.h"
#include "requests/qtdsendmessagerequest.h"
#include "requests/qtdsendmessagealbumrequest.h"
#include "requests/qtdgetchathistoryrequest.h"
#include "requests/qtdeditmessagetextrequest.h"
#include "requests/qtdeditmessagecaptionrequest.h"
#include "requests/content/qtdinputmessagetext.h"
#include "requests/content/qtdinputmessagevideo.h"
#include "requests/content/qtdinputmessageaudio.h"
#include "requests/content/qtdinputmessagedocument.h"
#include "requests/content/qtdinputmessageaudio.h"
#include "requests/content/qtdinputmessagecontact.h"
#include "requests/content/qtdinputmessagevideo.h"
#include "requests/content/qtdinputmessagelocation.h"
#include "requests/content/qtdinputmessagesticker.h"
#include "requests/content/qtdinputmessagevoicenote.h"
#include "requests/qtdgetmessagelinkrequest.h"
#include "qtdmessagecontentfactory.h"
#include "qtdmessagecontent.h"
#include "messages/requests/qtdviewmessagesrequest.h"
#include "messages/requests/qtddeletemessagesrequest.h"
#include "utils/i18n.h"
#include "common/qtdhelpers.h"
#include "utils/await.h"
#include "requests/content/imessageattachmentcontent.h"
#include "requests/content/imessagecaptioncontent.h"
#include "requests/content/qtdinputmessagephoto.h"
#include "chat/requests/qtdreportchatrequest.h"

Q_GLOBAL_STATIC(QAudioRecorder, m_voiceNoteRecorder)

QTdMessageListModel::QTdMessageListModel(QObject *parent)
    : QObject(parent)
    , m_model(Q_NULLPTR)
    , m_chat(Q_NULLPTR)
    , m_messageHandler(Q_NULLPTR)
    , m_jumpToMessageId(0)
    ,m_highlightJumpedMessage(false)
    , m_isHandleUpdateLastChatMessageConnected(false)
    , m_mediaSizeExtractor(new QTdMediaSizeExtractor(this))
{
    m_model = new QQmlObjectListModel<QTdMessage>(this, "", "id");
    connect(QTdClient::instance(), &QTdClient::messages, this, &QTdMessageListModel::handleMessages);
    connect(QTdClient::instance(), &QTdClient::updateMessageSendStatus, this, &QTdMessageListModel::handleUpdateMessageSendStatus);
    connect(QTdClient::instance(), &QTdClient::updateMessageContent, this, &QTdMessageListModel::handleUpdateMessageContent);
    connect(QTdClient::instance(), &QTdClient::updateDeleteMessages, this, &QTdMessageListModel::handleUpdateDeleteMessages);
    connect(QTdClient::instance(), &QTdClient::updateMessageEdited, this, &QTdMessageListModel::handleUpdateMessageEdited);
    connect(QTdClient::instance(), &QTdClient::updateFileGenerationStart, this, &QTdMessageListModel::handleUpdateFileGenerationStart);
    connect(QTdClient::instance(), &QTdClient::updateFileGenerationStop, this, &QTdMessageListModel::handleUpdateFileGenerationStop);
    connect(QTdClient::instance(), &QTdClient::updateMessageInteractionInfo, this, &QTdMessageListModel::handleUpdateMessageInteractionInfo);
    connect(QTdClient::instance(), &QTdClient::messageLink, this, &QTdMessageListModel::handleRequestMessageLinkCompleted);

    // check if m_voiceNoteRecorder has already been setup
    if (m_voiceNoteRecorder->outputLocation() == QUrl("")) {
        QScopedPointer<QAudioEncoderSettings> audioSettings(new QAudioEncoderSettings);
        audioSettings->setQuality(QMultimedia::HighQuality);
        audioSettings->setCodec("audio/x-opus");
        audioSettings->setSampleRate(16000);
        audioSettings->setEncodingMode(QMultimedia::ConstantQualityEncoding);
        audioSettings->setChannelCount(1);

        m_voiceNoteRecorder->setEncodingSettings(*audioSettings.take(), QVideoEncoderSettings(), "audio/ogg");
        m_voiceNoteRecorder->setVolume(1.0);

        QString path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/ok.ogg";
        m_voiceNoteRecorder->setOutputLocation(QUrl(path));
    }
}

QTdChat *QTdMessageListModel::chat() const
{
    return m_chat;
}

QObject *QTdMessageListModel::qmlModel() const
{
    return m_model;
}

bool QTdMessageListModel::isUpToDateAndFollowing() const
{
    return m_isHandleUpdateLastChatMessageConnected;
}

bool QTdMessageListModel::hasNewer() const
{
    if (m_model->isEmpty())
    {
        return false;
    }

    // when setting messages read, model is already up to date, but hasUnreadMessages still true
    bool hasUnread = m_chat->hasUnreadMessages();

    // this fails if the first message is a date label, which actually should never be the case
    bool lastMessageVisible = m_chat->lastMessage()->id() == m_model->first()->id();

    return hasUnread || !lastMessageVisible;
}

void QTdMessageListModel::setChat(QTdChat *chat)
{
    if (m_chat == chat && chat && chat->isOpen())
        return;
    if (m_chat)
    {
        disconnect(m_chat, &QTdChat::closed, this, &QTdMessageListModel::cleanUp);
    }

    if (!m_model->isEmpty())
    {
        cleanUp();
    }

    m_chat = chat;
    emit chatChanged(m_chat);

    if (!m_chat) {
        return;
    }

    connect(m_chat, &QTdChat::closed, this, &QTdMessageListModel::cleanUp);
    m_highlightJumpedMessage = false;
    if (m_chat->hasUnreadMessages()) {
        m_jumpToMessageId = m_chat->lastReadInboxMessageId();
        m_messageHandler = &jumpToWindowMessageHandler;
        loadMessages(m_chat->lastReadInboxMessageId(), MESSAGE_LOAD_WINDOW / 2, MESSAGE_LOAD_WINDOW / 2);
    } else {
        m_messageHandler = &olderMessagesHandler;
        QScopedPointer<QTdMessage> lastMessage(new QTdMessage());
        lastMessage->unmarshalJson(m_chat->lastMessageJson());
        loadMessages(lastMessage->id(), MESSAGE_LOAD_WINDOW, 1);
        connect(QTdClient::instance(), &QTdClient::updateChatLastMessage, this, &QTdMessageListModel::handleUpdateChatLastMessage);
    }
    m_chat->openChat();
}

void QTdMessageListModel::loadNewer()
{
    if (!m_chat) {
        return;
    }
    //This is to avoid loading messages when messages list is at the bottom (latest message shown)
    //and user scrolls down
    if (isUpToDateAndFollowing()) {
        return;
    }
    if (m_messageHandler) {
        return;
    }
    m_messageHandler = &newerMessagesHandler;
    loadMessages(m_model->first()->id(), 0, MESSAGE_LOAD_WINDOW);
}

void QTdMessageListModel::loadOlder()
{
    if (!m_chat) {
        return;
    }
    if (m_messageHandler) {
        return;
    }
    m_messageHandler = &olderMessagesHandler;
    loadMessages(m_model->last()->id(), MESSAGE_LOAD_WINDOW, 0);
}

void QTdMessageListModel::cleanUp()
{
    m_isHandleUpdateLastChatMessageConnected = false;
    disconnect(QTdClient::instance(), &QTdClient::updateChatLastMessage, this, &QTdMessageListModel::handleUpdateChatLastMessage);
    if (m_model->isEmpty()) {
        return;
    }
    m_model->clear();
}

void QTdMessageListModel::handleMessages(const QJsonObject &json)
{
    QJsonArray messages = json["messages"].toArray();
    if (messages.count() == 0) {
        if (m_model->count() > 0 && m_model->last()->id() != 0) {
            auto dateMessage = getDateLabelIfNeeded(m_model->last(), Q_NULLPTR);
            if (dateMessage) {
                m_model->append(dateMessage);
            }
        }
        m_messageHandler = Q_NULLPTR;
        return;
    }

    if (!m_messageHandler) {
        return;
    }

    m_messageHandler->handle(*this, messages);

    emit modelChanged();

    if (m_model->count() < MESSAGE_LOAD_WINDOW) {
        m_messageHandler = &olderMessagesHandler;
        qint64 lastValidMessageId;
        auto i = m_model->count() - 1;
        do {
            lastValidMessageId = m_model->at(i)->id();
        } while (--i > 0 && lastValidMessageId == 0);
        loadMessages(lastValidMessageId, MESSAGE_LOAD_WINDOW, 0);
    } else {
        m_messageHandler = Q_NULLPTR;
    }

    //When user jumped to an old message and the current view does not contain latest message
    //we don't want to enter this if block, otherwise scrolling down would not load messages
    //and messages list would be stuck in a wrong state.
    //hasNewer will tell if that is the case returning true when latest message is not in current messages list
    if (!hasNewer() && !m_isHandleUpdateLastChatMessageConnected) {
        connect(QTdClient::instance(), &QTdClient::updateChatLastMessage, this, &QTdMessageListModel::handleUpdateChatLastMessage);
        m_isHandleUpdateLastChatMessageConnected = true;
        m_chat->positionMessageListViewAtIndex(-1);
    }
}

void QTdMessageListModel::QTdOlderMessagesHandler::handle(QTdMessageListModel &messageListModel, const QJsonArray &messages) const
{
    for (unsigned int index = 0; index < messages.count(); index++) {
        auto *message = messageFromJson(messages[index]);
        messageListModel.appendMessage(message);
    }
}

void QTdMessageListModel::QTdNewerMessagesHandler::handle(QTdMessageListModel &messageListModel, const QJsonArray &messages) const
{
    QList<qint64> unreadMessages;

    for (int index = messages.count() - 1; index >= 0; index--) {
        auto *message = messageFromJson(messages[index]);
        messageListModel.prependMessage(message);
        unreadMessages << message->id();
    }

    messageListModel.setMessagesRead(unreadMessages);
}

void QTdMessageListModel::QTdJumpToWindowMessageHandler::handle(QTdMessageListModel &messageListModel, const QJsonArray &messages) const
{
    QList<qint64> unreadMessages;

    for (unsigned int index = 0; index < messages.count(); index++) {
        auto *message = messageFromJson(messages[index]);
        if (message->id() == messageListModel.m_chat->lastReadInboxMessageId() &&
            message->id() != messageListModel.m_chat->lastMessage()->id()) {
            auto *unreadLabel = new QTdMessage;
            unreadLabel->unmarshalJson(QJsonObject{ { "unreadLabel", gettext("Unread Messages") } });
            messageListModel.m_model->append(unreadLabel);
        }

        messageListModel.appendMessage(message);
        unreadMessages << message->id();
    }

    int jumpToMessageIndex = messageListModel.m_model->indexOf(QString::number(messageListModel.m_jumpToMessageId));
    messageListModel.m_chat->positionMessageListViewAtIndex(jumpToMessageIndex+1);
    messageListModel.setMessagesRead(unreadMessages);
    if (messageListModel.m_highlightJumpedMessage) {
        emit messageListModel.m_model->getByUid(QString::number(messageListModel.m_jumpToMessageId))->highlight();
    }
}

QTdMessage *QTdMessageListModel::getDateLabelIfNeeded(QTdMessage *firstMessage, QTdMessage *secondMessage)
{
    const QDate firstDate = firstMessage->qmlDate().date();
    const QDate secondDate = secondMessage
            ? secondMessage->qmlDate().date()
            : QDate();
    if (firstDate.year() > secondDate.year()
        || firstDate.month() > secondDate.month()
        || firstDate.day() > secondDate.day()) {
        auto *dateMessage = new QTdMessage;
        dateMessage->unmarshalJson(QJsonObject{ { "dateLabel", firstMessage->date() } });
        return dateMessage;
    } else {
        return Q_NULLPTR;
    }
}

void QTdMessageListModel::appendMessage(QTdMessage *message)
{
    if (m_model->isEmpty()) {
        m_model->append(message);
        return;
    }
    if (m_model->getByUid(message->qmlId())) {
        return;
    }
    auto *last = m_model->last();
    message->setPreviousSender(last->sender());
    last->setNextSender(message->sender());

    if (!message->sendingState()) {
        auto dateMessage = getDateLabelIfNeeded(last, message);
        if (dateMessage) {
            m_model->append(dateMessage);
        }
    }

    m_model->append(message);
}

void QTdMessageListModel::prependMessage(QTdMessage *message)
{
    if (m_model->isEmpty()) {
        m_model->prepend(message);
        return;
    }
    if (m_model->getByUid(message->qmlId())) {
        return;
    }
    auto *first = m_model->first();
    message->setNextSender(first->sender());
    first->setPreviousSender(message->sender());

    if (!message->sendingState()) {
        auto dateMessage = getDateLabelIfNeeded(message, first);
        if (dateMessage) {
            m_model->prepend(dateMessage);
        }
    }

    m_model->prepend(message);
}

void QTdMessageListModel::loadMessages(qint64 fromMsgId, unsigned int amountOlder, unsigned int amountNewer)
{
    QScopedPointer<QTdGetChatHistoryRequest> request(new QTdGetChatHistoryRequest);
    request->setChatId(m_chat->id());
    request->setFromMessageId(fromMsgId);
    request->setLimit(static_cast<int>(amountOlder + amountNewer + 1));
    request->setOffset(static_cast<int>(-amountNewer));
    request->sendAsync();
}

void QTdMessageListModel::handleUpdateChatLastMessage(const QJsonObject &json)
{
    if (!m_chat || json.isEmpty()) {
        return;
    }

    const qint64 id = json["chat_id"].toVariant().toLongLong();
    if (id != m_chat->id()) {
        return;
    }

    const QJsonObject messageJson = json["last_message"].toObject();

    const qint64 messageId = messageJson["id"].toVariant().toLongLong();
    auto *message = m_model->getByUid(QString::number(messageId));
    bool newMessage = false;
    if (!message) {
        message = new QTdMessage();
        newMessage = true;
    }
    message->unmarshalJson(messageJson);
    if (newMessage) {
        prependMessage(message);
        QList<qint64> unreadMessages;
        unreadMessages << messageId;
        setMessagesRead(unreadMessages);
    }

    emit modelChanged();
}

void QTdMessageListModel::handleUpdateMessageSendStatus(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    const qint64 oldMid = json["old_message_id"].toVariant().toLongLong();
    auto *msgSent = m_model->getByUid(QString::number(oldMid));
    if (msgSent) {
        const QJsonObject message = json["message"].toObject();
        msgSent->unmarshalJson(message);
    }
    if (json["@type"].toString() == "updateMessageSendFailed") {
        qWarning() << "Message send error" << json["error_code"].toVariant().toLongLong() << json["error_message"].toString();
    }
}

void QTdMessageListModel::handleUpdateMessageEdited(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    auto messageId = QString::number(json["message_id"].toVariant().toLongLong(), 'f', 0);
    QTdMessage *message = m_model->getByUid(messageId);
    if (!message) {
        return;
    }
    message->setIsEdited(true);
}

void QTdMessageListModel::handleUpdateDeleteMessages(const QJsonObject &json)
{
    if (json.isEmpty() || json["from_cache"].toBool()) {
        return;
    }
    const QJsonArray messagesToDelete = json["message_ids"].toArray();
    foreach (QJsonValue messageToDelete, messagesToDelete) {
        qint64 id = messageToDelete.toVariant().toLongLong();
        auto messageId = QString::number(id, 'f', 0);
        QTdMessage *message = m_model->getByUid(messageId);
        if (!message) {
            continue;
        }
        foreach (QTdMessage *msg, m_model->toList()) {
            if (msg->messageRepliedTo() && msg->messageRepliedTo()->id() == id) {
                msg->messageRepliedTo()->unmarshalJson(QJsonObject{{"date",0}});
                emit msg->messageRepliedToChanged();
            }
        }
        m_model->remove(message);
    }
}

void QTdMessageListModel::handleUpdateMessageContent(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    const qint64 messageId = json["message_id"].toVariant().toLongLong();
    const QJsonObject newContent = json["new_content"].toObject();
    QTdMessage *message = m_model->getByUid(QString::number(messageId));
    if (!message) {
        return;
    }
    message->unmarshalUpdateContent(newContent);
}

void QTdMessageListModel::sendMessage(const QString &fullmessage, const bool clearDraft, const bool disableNotification, const qint32 sendDate, const QString &replyToMessageId)
{
    if (!m_chat) {
        return;
    }
    QString plainText;
    QJsonArray formatEntities = QTdHelpers::formatPlainTextMessage(fullmessage, plainText);
    bool isFirstMessage = true;
    qint32 currentMessagePos = 0;
    qint32 currentMessageLength = 0;
    qint32 maxMessageLength = QTdClient::instance()->getOption("message_text_length_max").toInt();
    do {
        QString message = plainText.mid(currentMessagePos, maxMessageLength);
        QScopedPointer<QTdSendMessageRequest> request(new QTdSendMessageRequest);
        request->setChatId(m_chat->id());
        request->setDisableNotification(disableNotification);
        request->setSendDate(sendDate);
        QScopedPointer<QTdInputMessageText> messageText(new QTdInputMessageText);
        messageText->setText(message);
        messageText->setEntities(formatEntities);
        messageText->setClearDraft(clearDraft);
        request->setContent(messageText.data());
        if (isFirstMessage) {
            request->setReplyToMessageId(replyToMessageId.toLongLong());
            isFirstMessage = false;
        }
        currentMessageLength = message.length();
        request->sendAsync();
        currentMessagePos += maxMessageLength;
    } while (currentMessagePos < plainText.length());
}

void QTdMessageListModel::setCaptionProperties(IMessageCaptionContent *contentObj, const QString &caption)
{
    if (contentObj != nullptr) {
        QString plainText;
        qint32 maxCaptionLength = QTdClient::instance()->getOption("message_caption_length_max").toInt();
        QJsonArray formatEntities = QTdHelpers::formatPlainTextMessage(caption, plainText);
        contentObj->setCaption(plainText.left(maxCaptionLength));
        contentObj->setCaptionEntities(formatEntities);
    }
}

void QTdMessageListModel::setAttachmentProperties(IMessageAttachmentContent *contentObj, const QString &attachmentUrl)
{
    if (contentObj != nullptr) {
        contentObj->setAttachmentPath(attachmentUrl);
    }
}

void QTdMessageListModel::prepareAndSendAttachmentMessage(QTdInputMessageContent *content, const qint64 &replyToMessageId)
{
    if (!m_chat) {
        return;
    }
    QScopedPointer<QTdSendMessageRequest> request(new QTdSendMessageRequest);
    request->setChatId(m_chat->id());
    request->setContent(content);
    request->setReplyToMessageId(replyToMessageId);
    QTdClient::instance()->sendAsync(request.data(), &QTdClient::message);
}

void QTdMessageListModel::prepareAndSendAttachmentMessageAlbum(QList<QTdInputMessageContent *> &contents, const qint64 &replyToMessageId)
{
    if (!m_chat) {
        return;
    }
    QScopedPointer<QTdSendMessageAlbumRequest> request(new QTdSendMessageAlbumRequest);
    request->setChatId(m_chat->id());
    request->setContents(contents);
    request->setReplyToMessageId(replyToMessageId);
    QTdClient::instance()->sendAsync(request.data(), &QTdClient::message);
}

void QTdMessageListModel::sendMedia(const QString &url, const QString &caption, const qint64 &replyToMessageId, InputMessageType inputMessageType)
{
    QTdInputMessageContentAttachmentCaption* messageContent(QTdInputMessageContentFactory::create(inputMessageType));
    setAttachmentProperties(messageContent, url);
    setCaptionProperties(messageContent, caption);
    prepareAndSendAttachmentMessage(messageContent, replyToMessageId);
}

void QTdMessageListModel::sendPhoto(const QString &url, const QString &caption, const qint64 &replyToMessageId)
{
    sendMedia(url, caption, replyToMessageId, Photo);
}

void QTdMessageListModel::sendPhotoAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId)
{
    sendAlbum(urls, caption, replyToMessageId, Photo);
}

void QTdMessageListModel::sendVideoAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId)
{
    sendAlbum(urls, caption, replyToMessageId, Video);
}

void QTdMessageListModel::sendAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId, const InputMessageType type)
{
    //sendMessageAlbum size must be between 2 and 10
    //so if we have more than 10 urls we send multiple messageAlbum
    for (int i = 0; i < urls.size(); i+=10) {
        QList<QTdInputMessageContent *> messageContents;
        for (int j = 0; j < 10 && j+i < urls.size(); j++) {
            QTdInputMessageContentAttachmentCaption *messageContent = QTdInputMessageContentFactory::create(type);
            setAttachmentProperties(messageContent, urls.at(j+i));
            if (i == 0 && j == 0) {
                setCaptionProperties(messageContent, caption);
            }
            messageContents.append(messageContent);
        }
        prepareAndSendAttachmentMessageAlbum(messageContents, replyToMessageId);
    }
}

void QTdMessageListModel::sendAudio(const QString &url, const QString &caption, const qint64 &replyToMessageId)
{
    sendMedia(url, caption, replyToMessageId, Audio);
}

void QTdMessageListModel::sendAudioAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId)
{
    sendAlbum(urls, caption, replyToMessageId, Audio);
}

void QTdMessageListModel::sendVideo(const QString &url, const QString &caption, const qint64 &replyToMessageId)
{
    sendMedia(url, caption, replyToMessageId, Video);
}

void QTdMessageListModel::sendContact(const QString &firstName, const QString &lastName, const QString &phone, const qint64 &replyToMessageId)
{
    QScopedPointer<QTdInputMessageContact> messageContent(new QTdInputMessageContact);
    messageContent->contact()->setFirstName(firstName);
    messageContent->contact()->setLastName(lastName);
    messageContent->contact()->setPhoneNumber(phone);
    prepareAndSendAttachmentMessage(messageContent.data(), replyToMessageId);
}

void QTdMessageListModel::sendDocument(const QString &url, const QString &caption, const qint64 &replyToMessageId)
{
    sendMedia(url, caption, replyToMessageId, Document);
}

void QTdMessageListModel::sendDocumentAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId)
{
    sendAlbum(urls, caption, replyToMessageId, Document);
}

void QTdMessageListModel::sendLocation(const double latitude, const double longitude, const qint32 livePeriod, const qint64 &replyToMessageId)
{
    QScopedPointer<QTdInputMessageLocation> messageContent(new QTdInputMessageLocation);
    messageContent->setLocation(latitude, longitude);
    messageContent->setLivePeriod(livePeriod);
    prepareAndSendAttachmentMessage(messageContent.data(), replyToMessageId);
}

void QTdMessageListModel::sendSticker(QTdSticker *sticker, const QString &replyToMessageId)
{
    QScopedPointer<QTdInputMessageSticker> messageContent(new QTdInputMessageSticker);
    messageContent->setSticker(sticker);
    prepareAndSendAttachmentMessage(messageContent.data(), replyToMessageId.toLongLong());
}

void QTdMessageListModel::sendVoiceNote(const QString &filename, const qint64 &replyToMessageId)
{
    if (m_voiceNoteRecorder->duration() > 0) {
        QScopedPointer<QTdInputMessageVoiceNote> messageContent(new QTdInputMessageVoiceNote);
        setAttachmentProperties(messageContent.data(), filename);
        prepareAndSendAttachmentMessage(messageContent.data(), replyToMessageId);
    }
}

void QTdMessageListModel::editMessageText(qint64 messageId, const QString &message)
{
    if (!m_chat) {
        return;
    }

    QString plainText;
    QJsonArray formatEntities = QTdHelpers::formatPlainTextMessage(message, plainText);

    QScopedPointer<QTdEditMessageTextRequest> request(new QTdEditMessageTextRequest);
    request->setChatId(m_chat->id());
    request->setMessageId(messageId);
    request->setText(plainText);
    request->setEntities(formatEntities);

    QFuture<QTdResponse> response = request->sendAsync();
    await(response);
    if (response.result().isError()) {
        emit error(response.result().errorString());
    }
}

void QTdMessageListModel::editMessageText(const QString &messageId, const QString &message)
{
    editMessageText(messageId.toLongLong(), message);
}

void QTdMessageListModel::editMessageCaption(qint64 messageId, const QString &message)
{
    if (!m_chat) {
        return;
    }

    QString plainText;
    QJsonArray formatEntities = QTdHelpers::formatPlainTextMessage(message, plainText);

    QScopedPointer<QTdEditMessageCaptionRequest> request(new QTdEditMessageCaptionRequest);
    request->setChatId(m_chat->id());
    request->setMessageId(messageId);
    request->setText(plainText);
    request->setEntities(formatEntities);

    QFuture<QTdResponse> response = request->sendAsync();
    await(response);
    if (response.result().isError()) {
        emit error(response.result().errorString());
    }
}

void QTdMessageListModel::editMessageCaption(const QString &messageId, const QString &message)
{
    editMessageCaption(messageId.toLongLong(), message);
}

void QTdMessageListModel::deleteMessage(const qint64 messageId, const bool revoke)
{
    QList<qint64> messages;
    messages << messageId;
    deleteMessages(messages, revoke);
}

void QTdMessageListModel::deleteMessages(const QList<qint64> &messageIds, const bool revoke)
{
    QScopedPointer<QTdDeleteMessagesRequest> req(new QTdDeleteMessagesRequest);
    req->setChatId(m_chat->id());
    req->setMessageIds(messageIds);
    req->setRevoke(revoke);
    QTdClient::instance()->send(req.data());
}

void QTdMessageListModel::setMessagesRead(QList<qint64> &messages)
{
    // TODO: Determine how to detect which messages are in the visible part of the window
    QScopedPointer<QTdViewMessagesRequest> req(new QTdViewMessagesRequest);
    req->setChatId(m_chat->id());
    req->setMessageIds(messages);
    QTdClient::instance()->send(req.data());
    if (messages.contains(m_chat->lastMessage()->id())) {
        QTdClient::instance()->clearNotificationFor(m_chat->id());
    }
}

void QTdMessageListModel::jumpToMessage(const qint64 messageId, const bool isToBeHighlighted)
{
    int messageToJumpToIndex = m_model->indexOf(QString::number(messageId));
    if (messageToJumpToIndex > -1) {
        m_chat->positionMessageListViewAtIndex(messageToJumpToIndex+1);
        if (isToBeHighlighted) {
            emit m_model->getByUid(QString::number(messageId))->highlight();
        }
    } else {
        cleanUp();
        m_jumpToMessageId = messageId;
        m_highlightJumpedMessage = isToBeHighlighted;
        m_isHandleUpdateLastChatMessageConnected = false;
        m_messageHandler = &jumpToWindowMessageHandler;
        loadMessages(messageId, MESSAGE_LOAD_WINDOW / 2, MESSAGE_LOAD_WINDOW / 2);
    }
}

void QTdMessageListModel::handleUpdateFileGenerationStart(const QJsonObject &json)
{
    QString destinationPath = json["destination_path"].toString();
    if (QFile::exists(destinationPath)) {
        QFile::remove(destinationPath);
    }

    m_fileGenerationId = json["generation_id"].toString();
    QJsonObject finishReq = QJsonObject {
        { "@type", "finishFileGeneration" },
        { "generation_id", m_fileGenerationId }
    };
    QString originalPath = json["original_path"].toString();
    QString conversion = json["conversion"].toString();
    bool result;
    if (conversion == "attachment") {
        result = QFile::copy(originalPath, destinationPath);
    } else {
        result = QFile::rename(originalPath, destinationPath);
    }
    if (!result) {
        qWarning() << "Could not move" << originalPath << "to" << destinationPath;
        QJsonObject error = QJsonObject {
            { "@type", "error" },
            { "code", "500" }
        };
        finishReq.insert("error", error);
    }
    QTdClient::instance()->send(finishReq);
    emit importFileFinished(originalPath);
}

void QTdMessageListModel::handleUpdateFileGenerationStop(const QJsonObject &json)
{
    m_fileGenerationId = "";
}

void QTdMessageListModel::handleUpdateMessageInteractionInfo(const QJsonObject &json)
{

    auto chatId = qint64(json["chat_id"].toDouble());
    if (!m_chat || m_chat->id() != chatId) {
        return;
    }

    auto messageId = qint64(json["message_id"].toDouble());
    auto message = m_model->getByUid(QString::number(messageId));
    if (!message) {
        return;
    }

    auto interactionInfo = json["interaction_info"].toObject();
    message->interactionInfo()->unmarshalJson(interactionInfo);
}

void QTdMessageListModel::handleRequestMessageLinkCompleted(const QJsonObject &json)
{
    auto link = json["link"].toString();
    emit messageLinkReceived(link);
}

void QTdMessageListModel::registerVoiceNote(const QString &filename)
{
    m_voiceNoteRecorder->setOutputLocation(QUrl(filename));
    m_voiceNoteRecorder->record();
}

void QTdMessageListModel::stopVoiceNote()
{
    qWarning() << "Stopping voice note recording";
    m_voiceNoteRecorder->stop();
}

void QTdMessageListModel::deleteVoiceNote(const QString &filename)
{
    QFile file(filename);
    if (!file.remove()) {
        qWarning() << "Could not delete temp voice note:" << filename;
    }
}

void QTdMessageListModel::removeChatActionBar()
{
    QJsonObject removeChatActionBarRequest = QJsonObject {
        { "@type", "removeChatActionBar" },
        { "chat_id", m_chat->id() }
    };
    QTdClient::instance()->send(removeChatActionBarRequest);
}

void QTdMessageListModel::reportChat(const QString chatId, const QTdChatReportReason::ChatReportReasonType &reason, const QString &text)
{

    QScopedPointer<QTdReportChatRequest> req(new QTdReportChatRequest);
    req->setChatId(chatId);
    // req->setMessageIds(messages);
    QScopedPointer<QTdChatReportReason> reasonObj;
    switch (reason) {
    case QTdChatReportReason::ChatReportReasonChildAbuse:
        reasonObj.reset(new QTdChatReportReasonChildAbuse());
        break;
    case QTdChatReportReason::ChatReportReasonCopyright:
        reasonObj.reset(new QTdChatReportReasonCopyright());
        break;
    case QTdChatReportReason::ChatReportReasonCustom:
        reasonObj.reset(new QTdChatReportReasonCustom());
        break;
    case QTdChatReportReason::ChatReportReasonFake:
        reasonObj.reset(new QTdChatReportReasonFake());
        break;
    case QTdChatReportReason::ChatReportReasonPornography:
        reasonObj.reset(new QTdChatReportReasonPornograhpy());
        break;
    case QTdChatReportReason::ChatReportReasonSpam:
        reasonObj.reset(new QTdChatReportReasonSpam());
        break;
    case QTdChatReportReason::ChatReportReasonUnrelatedLocation:
        reasonObj.reset(new QTdChatReportReasonUnrelatedLocation());
        break;
    case QTdChatReportReason::ChatReportReasonViolence:
        reasonObj.reset(new QTdChatReportReasonViolence());
        break;
    }
    req->setReason(reasonObj.data());
    req->setText(text);
    req->sendAsync();
}

void QTdMessageListModel::requestMessageLink(const QString chatId, const QString messageId)
{
    QScopedPointer<QTdGetMessageLinkRequest> req(new QTdGetMessageLinkRequest);
    req->setChatId(chatId.toLong());
    req->setMessageId(messageId.toLong());
    req->sendAsync();
}
