#ifndef QTDMESSAGELISTMODEL_H
#define QTDMESSAGELISTMODEL_H

#include <QObject>
#include <QPointer>
#include <QDebug>
#include "chat/qtdchat.h"
#include "models/QmlObjectListModel.h"
#include "qtdchatstate.h"
#include "qtdmessage.h"
#include "requests/qtdinputmessagecontent.h"
#include "requests/qtdinputmessagecontentfactory.h"
#include "requests/content/imessageattachmentcontent.h"
#include "requests/content/imessagecaptioncontent.h"
#include "chat/requests/qtdchatreportreason.h"
#include "chat/requests/qtdreportchatrequest.h"
#include "../utils/qtdmediatools.h"

#define MESSAGE_LOAD_WINDOW 60

class QTdMessageListModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QTdChat *chat READ chat WRITE setChat NOTIFY chatChanged)
    Q_PROPERTY(QObject *model READ qmlModel NOTIFY modelChanged)

public:
    explicit QTdMessageListModel(QObject *parent = nullptr);

    QTdChat *chat() const;
    QObject *qmlModel() const;

    class QTdAbstractMessageHandler : public QObject
    {
    public:
        virtual ~QTdAbstractMessageHandler() {}
        virtual void handle(QTdMessageListModel &messageListModel, const QJsonArray &messages) const = 0;
        QTdMessage *messageFromJson(const QJsonValue &msgData) const
        {
            const QJsonObject data = msgData.toObject();
            auto *message = new QTdMessage;
            message->unmarshalJson(data);
            return message;
        }
    };

    class QTdNewerMessagesHandler : public QTdAbstractMessageHandler
    {
        void handle(QTdMessageListModel &messageListModel, const QJsonArray &messages) const;
    };

    class QTdOlderMessagesHandler : public QTdAbstractMessageHandler
    {
        void handle(QTdMessageListModel &messageListModel, const QJsonArray &messages) const;
    };

    class QTdJumpToWindowMessageHandler : public QTdAbstractMessageHandler
    {
        void handle(QTdMessageListModel &messageListModel, const QJsonArray &messages) const;
    };

signals:
    void chatChanged(QTdChat *chat);
    void modelChanged();
    void importFileFinished(QString fileName);
    void error(const QString &errorMessage);
    void messageLinkReceived(const QString messageLink);

public slots:
    void setChat(QTdChat *chat);
    void loadNewer();
    void loadOlder();

    void setCaptionProperties(IMessageCaptionContent *contentObj, const QString &caption);
    void setAttachmentProperties(IMessageAttachmentContent *contentObj, const QString &attachmentUrl);
    void prepareAndSendAttachmentMessage(QTdInputMessageContent *contentObj, const qint64 &replyToMessageId);
    void prepareAndSendAttachmentMessageAlbum(QList<QTdInputMessageContent*> &contents, const qint64 &replyToMessageId);
    void sendMessage(const QString &message, const bool clearDraft = false, const bool disableNotification = false, const qint32 sendDate = 0, const QString &replyToMessageId = "0");

    void sendPhoto(const QString &url, const QString &caption, const qint64 &replyToMessageId);
    void sendAudio(const QString &url, const QString &caption, const qint64 &replyToMessageId);
    void sendAudioAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId);
    void sendVideo(const QString &url, const QString &caption, const qint64 &replyToMessageId);
    void sendPhotoAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId);
    void sendVideoAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId);
    void sendContact(const QString &firstName, const QString &lastName, const QString &phone, const qint64 &replyToMessageId);
    void sendDocument(const QString &url, const QString &caption, const qint64 &replyToMessageId);
    void sendDocumentAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId);
    void sendLocation(const double latitude, const double longitude, const qint32 livePeriod, const qint64 &replyToMessageId);
    void sendSticker(QTdSticker *sticker, const QString &replyToMessageId = "");
    void sendVoiceNote(const QString &filename, const qint64 &replyToMessageId);

    void editMessageText(qint64 messageId, const QString &message);
    void editMessageText(const QString &messageId, const QString &message);
    void editMessageCaption(qint64 messageId, const QString &message);
    void editMessageCaption(const QString &messageId, const QString &message);
    //void sendReplyToMessage(const qint64 &replyToMessageId, const QString &message, const bool disableNotification = false, const qint32 sendDate = 0);
    //void sendReplyToMessage(const QString &replyToMessageId, const QString &message, const bool disableNotification = false, const qint32 sendDate = 0);
    //sendMessage(message, true, replyToMessageId, disableNotification, sendDate);
    void deleteMessage(const qint64 messageId, const bool revoke);
    void deleteMessages(const QList<qint64> &messageIds, const bool revoke);
    void jumpToMessage(const qint64 messageId, const bool isToBeHighlighted);
    void registerVoiceNote(const QString &filename);
    void stopVoiceNote();
    void deleteVoiceNote(const QString &filename);
    void handleUpdateFileGenerationStart(const QJsonObject &json);
    void handleUpdateFileGenerationStop(const QJsonObject &json);
    void handleUpdateMessageInteractionInfo(const QJsonObject &json);
    
    void removeChatActionBar();
    void reportChat(const QString chatId, const QTdChatReportReason::ChatReportReasonType &reason, const QString &text);
    void requestMessageLink(const QString chatId, const QString messageId);
    
private slots:
    void cleanUp();
    void handleMessages(const QJsonObject &json);
    void handleUpdateChatLastMessage(const QJsonObject &json);
    void handleUpdateMessageSendStatus(const QJsonObject &json);
    void handleUpdateMessageContent(const QJsonObject &json);
    void handleUpdateDeleteMessages(const QJsonObject &json);
    void handleUpdateMessageEdited(const QJsonObject &json);
    void loadMessages(qint64 fromMsgId,
                      unsigned int amountBefore,
                      unsigned int amountAfter);
    void handleRequestMessageLinkCompleted(const QJsonObject &json);

private:
    Q_DISABLE_COPY(QTdMessageListModel)
    QPointer<QQmlObjectListModel<QTdMessage>> m_model;
    QPointer<QTdChat> m_chat;
    QPointer<QTdAbstractMessageHandler> m_messageHandler;
    QTdNewerMessagesHandler newerMessagesHandler;
    QTdOlderMessagesHandler olderMessagesHandler;
    QTdJumpToWindowMessageHandler jumpToWindowMessageHandler;
    bool m_isHandleUpdateLastChatMessageConnected;
    qint64 m_jumpToMessageId;
    bool m_highlightJumpedMessage;
    QString m_fileGenerationId;
    QScopedPointer<QTdMediaSizeExtractor> m_mediaSizeExtractor;

    QTdMessage *getDateLabelIfNeeded(QTdMessage *firstMessage, QTdMessage *secondMessage);
    void setMessagesRead(QList<qint64> &messages);
    void appendMessage(QTdMessage *message);
    void prependMessage(QTdMessage *message);
    bool isUpToDateAndFollowing() const;
    bool hasNewer() const;
    void sendMedia(const QString &url, const QString &caption, const qint64 &replyToMessageId, InputMessageType inputMessageType);
    void sendAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId, const InputMessageType type);
};

#endif // QTDMESSAGELISTMODEL_H
