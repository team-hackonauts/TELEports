#ifndef QTDMESSAGE_H
#define QTDMESSAGE_H

#include <QDateTime>
#include <QObject>
#include <QPointer>

#include "common/qabstractint64id.h"
#include "qtdmessagecontent.h"
#include "qtdmessageinteractioninfo.h"
#include "qtdmessagesender.h"
#include "qtdmessagesendingstate.h"
#include "qtdmessageschedulingstate.h"
#include "replymarkup/qtdreplymarkup.h"
#include "forwardinfo/qtdmessageforwardinfo.h"
#include "user/qtduser.h"

class QTdMessage : public QAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QTdMessageSender *sender READ sender NOTIFY senderChanged)
    Q_PROPERTY(QString chatId READ qmlChatId NOTIFY messageChanged)
    Q_PROPERTY(QTdMessageSendingState *sendingState READ sendingState NOTIFY sendingStateChanged)
    Q_PROPERTY(QTdMessageSchedulingState *schedulingState READ schedulingState NOTIFY messageChanged)
    Q_PROPERTY(bool isOutgoing READ isOutgoing NOTIFY messageChanged)
    Q_PROPERTY(bool isPinned READ isPinned NOTIFY messageChanged)
    Q_PROPERTY(bool canBeEdited READ canBeEdited NOTIFY messageChanged)
    Q_PROPERTY(bool canBeForwarded READ canBeForwarded NOTIFY messageChanged)
    Q_PROPERTY(bool canBeSaved READ canBeSaved NOTIFY messageChanged)
    Q_PROPERTY(bool canBeDeletedOnlyForSelf READ canBeDeletedOnlyForSelf NOTIFY messageChanged)
    Q_PROPERTY(bool canBeDeletedForAllUsers READ canBeDeletedForAllUsers NOTIFY messageChanged)
    Q_PROPERTY(bool canGetStatistics READ canGetStatistics NOTIFY messageChanged)
    Q_PROPERTY(bool canGetMessageThread READ canGetMessageThread NOTIFY messageChanged)
    Q_PROPERTY(bool canGetViewers READ canGetViewers NOTIFY messageChanged)
    Q_PROPERTY(bool canGetMediaTimestampLinks READ canGetMediaTimestampLinks NOTIFY messageChanged)
    Q_PROPERTY(bool hasTimestampedMedia READ hasTimestampedMedia NOTIFY messageChanged)
    Q_PROPERTY(bool isChannelPost READ isChannelPost NOTIFY messageChanged)
    Q_PROPERTY(bool containsUnreadMention READ containsUnreadMention NOTIFY messageChanged)
    Q_PROPERTY(QDateTime date READ qmlDate NOTIFY messageChanged)
    Q_PROPERTY(QDateTime editDate READ qmlEditDate NOTIFY messageChanged)
    Q_PROPERTY(QTdMessageForwardInfo *forwardInfo READ forwardInfo NOTIFY messageChanged)
    Q_PROPERTY(QTdMessageInteractionInfo *interactionInfo READ interactionInfo NOTIFY messageChanged)
    Q_PROPERTY(QString replyToMessageId READ qmlReplyToMessageId NOTIFY messageChanged)
    Q_PROPERTY(QString messageThreadId READ qmlMessageThreadId NOTIFY messageChanged)
    Q_PROPERTY(qint32 ttl READ ttl NOTIFY messageChanged)

    Q_PROPERTY(bool isEdited READ isEdited WRITE setIsEdited NOTIFY messageChanged)
    Q_PROPERTY(QString views READ views NOTIFY messageChanged)
    Q_PROPERTY(QTdMessageContent *content READ content NOTIFY messageChanged)
    Q_PROPERTY(QTdReplyMarkup *replyMarkup READ replyMarkup NOTIFY messageChanged)
    // These aren't original properties of the tdlib message class but we can
    // can make life easier for use in QML.
    // Provide a summary text for display in the chatlist
    Q_PROPERTY(QString summary READ summary NOTIFY senderChanged)
    // Shows if the sender of the previous message is the same as this one.
    Q_PROPERTY(bool sameSenderAsPreviousMessage READ sameSenderAsPreviousMessage NOTIFY previousSenderChanged)
    // Shows if the sender of the next message is the same as this one.
    Q_PROPERTY(bool sameSenderAsNextMessage READ sameSenderAsNextMessage NOTIFY nextSenderChanged)
    // Indicates if this message is the first/latest message in the model
    Q_PROPERTY(bool isLatest READ isLatest NOTIFY nextSenderChanged)
    Q_PROPERTY(QTdMessage *messageRepliedTo READ messageRepliedTo NOTIFY messageRepliedToChanged)
    Q_PROPERTY(bool isReply READ isReply NOTIFY messageChanged)
    Q_PROPERTY(bool isCollapsed READ isCollapsed NOTIFY messageChanged)
    Q_PROPERTY(bool isForwarded READ isForwarded NOTIFY messageChanged)

public:
    explicit QTdMessage(QObject *parent = nullptr);

    QString qmlChatId() const;
    qint64 chatId() const;
    QString getSenderInitials() const;

    QTdMessageSender *sender() const;

    void unmarshalJson(const QJsonObject &json) override;
    void unmarshalUpdateContent(const QJsonObject &content);

    QTdMessageSendingState *sendingState() const;

    QTdMessageSchedulingState *schedulingState() const;

    bool isOutgoing() const;

    bool isPinned() const;

    bool isEdited() const;

    void setIsEdited(const bool value);

    bool canBeEdited() const;

    bool canBeForwarded() const;

    bool canBeSaved() const;

    bool canBeDeletedOnlyForSelf() const;

    bool canBeDeletedForAllUsers() const;

    bool canGetStatistics() const;

    bool canGetMessageThread() const;

    bool canGetViewers() const;

    bool canGetMediaTimestampLinks() const;

    bool hasTimestampedMedia() const;

    bool isChannelPost() const;

    bool containsUnreadMention() const;

    QDateTime qmlDate() const;
    qint32 date() const;

    QDateTime qmlEditDate() const;
    qint32 editDate() const;

    QTdMessageForwardInfo *forwardInfo() const;

    QTdMessageInteractionInfo *interactionInfo() const;

    qint64 replyToMessageId() const;
    QString qmlReplyToMessageId() const;

    qint64 messageThreadId() const;
    QString qmlMessageThreadId() const;

    qint32 ttl() const;



    QString views() const;


    QTdMessageContent *content() const;

    QTdReplyMarkup *replyMarkup() const;

    bool isForwarded() const;

    QString summary() const;

    Q_INVOKABLE QString formatDate(const QDateTime &dt);

    bool isValid() const;

    bool sameSenderAsPreviousMessage() const;

    void setPreviousSender(QTdMessageSender *sender);

    bool sameSenderAsNextMessage() const;

    void setNextSender(QTdMessageSender *sender);

    bool isLatest() const;

    bool isCollapsed() const;

    void collapse();

    bool isReply() const;
    QTdMessage *messageRepliedTo();

signals:
    void messageChanged();
    void senderChanged();
    void sendingStateChanged();
    void previousSenderChanged();
    void nextSenderChanged();
    void messageRepliedToChanged();
    void highlight();

private slots:
    void updateSendingState(const QJsonObject &json);
    void updateSchedulingState(const QJsonObject &json);
    void handleMessage(const QJsonObject &json);

private:
    QScopedPointer<QTdMessageSender> m_sender;
    QTdInt64 m_chatId;
    QScopedPointer<QTdMessageSendingState> m_sendingState;
    QScopedPointer<QTdMessageSchedulingState> m_schedulingState;
    bool m_isOutgoing;
    bool m_isPinned;
    bool m_canBeEdited;
    bool m_canBeForwarded;
    bool m_canBeSaved;
    bool m_canBeDeletedOnlyForSelf;
    bool m_canBeDeletedForAllUsers;
    bool m_canGetStatistics;
    bool m_canGetMessageThread;
    bool m_canGetViewers;
    bool m_canGetMediaTimestampLinks;
    bool m_hasTimestampedMedia;
    bool m_isChannelPost;
    bool m_containsUnreadMention;
    qint32 m_date;
    qint32 m_editDate;
    QScopedPointer<QTdMessageForwardInfo> m_forwardInfo;
    QScopedPointer<QTdMessageInteractionInfo> m_interactionInfo;
    qint64 m_replyInChatId;
    QTdInt64 m_replyToMessageId;
    QTdInt64 m_messageThreadId;
    qint32 m_ttl;
    qint64 m_viaBotUserId;
    qint64 m_mediaAlbumId;
    QString m_restrictionReason;
    QScopedPointer<QTdMessageContent> m_content;
    QScopedPointer<QTdReplyMarkup> m_replyMarkup;

    bool m_isEdited;
    bool m_isValid;
    QPointer<QTdMessageSender> m_previousSender, m_nextSender;
    QPointer<QTdMessage> m_messageRepliedTo;
    bool m_isCollapsed;

};

#endif // QTDMESSAGE_H
