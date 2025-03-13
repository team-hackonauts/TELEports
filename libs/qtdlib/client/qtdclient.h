#ifndef QTDCLIENT_H
#define QTDCLIENT_H

#include <functional>
#include <QObject>
#include <QPointer>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QHash>
#include <QFuture>
#include <QThread>
#include <QJsonObject>
#include <QtConcurrent>
#include <QWaitCondition>
#include "auth/qtdauthstate.h"
#include "connections/qtdconnectionstate.h"
#include "common/qtdrequest.h"
#include "common/qtdresponse.h"
#include "../../common/auxdb/auxdb.h"
#include "../../common/auxdb/postal-client.h"

// callback to trigger on received messages from tdlib.
typedef std::function<void(QJsonObject)> ReceiveCallback;

/**
 * @brief The QTdClient class
 *
 * QTdClient is the main interface for communication with
 * the tdlib backend. A static instance is used to easily share
 * between components.
 */
class QTdClient : public QObject
{
    Q_OBJECT
public:
    explicit QTdClient(QObject *parent = nullptr);

    /**
     * @brief Shared static instance in the main thread.
     */
    static QTdClient *instance();

    /**
     * @brief The current authentication state
     */
    QTdAuthState *authState() const;
    /**
     * @brief The current connection state
     */
    QTdConnectionState *connectionState() const;

    /**
     * @brief send
     *
     * Send a request in another thread.
     */
    void send(QTdRequest *obj);
    void send(const QJsonObject &json);

    /**
     * @brief sendAsync
     * @param obj is the QTdRequest to send
     * @param void(QTdClient::*s)(QJsonObject) is the signal the response will come down
     * @return QFuture<QTdResponse> - QTdResponse will either contain an `error` or the requested return types json object
     *
     * Send an asynchronous request that can be waited on for a response.
     *
     * @example
     * QScopedPointer<QTdGetChatsRequest> req(new QTdGetChatsRequest);
     *
     * The response to getChats comes down the `chats` signal
     * QFuture<QTdResponse> resp = QTdClient::instance()->sendAsync(req, &QTdClient::chats);
     *
     * You can either use a QFutureWatcher to wait for the resp or you can use the new
     * `await` helper `#include "utils/await.h"` which uses QFutureWatcher internally but also allows a timeout
     * so you don't wait forever.
     * await(resp);
     *
     * if (resp.result().isError()) {
     *   // handle error
     *   qWarning() << resp.result().errorCode() << resp.result().errorString();
     * }
     * // access json
     * qDebug() << resp.result().json()
     *
     */
    QFuture<QTdResponse> sendAsync(QTdRequest *obj, void (QTdClient::*signal)(QJsonObject));

    /**
     * @brief Execute synchronous request in another Thread
     *
     * This is a synchronous action in another
     * thread and will return the result via the
     * returned QFuture
     *
     * Note: there is only a limited set of actions that can be sent
     * through exec. Still need to figure out what they are. Once
     * found it will be indicated in each QTdRequest derived class
     * documentation
     */
    QFuture<QJsonObject> exec(QTdRequest *obj);
    QFuture<QJsonObject> exec(const QJsonObject &json);

    /**
     * @brief Retrieve a Telegram server option by name
     *
     * Retrieves an option that has been received from the Telegram server upon login or after an update
     * Clients should subscribe for the updateOption signal and then call this method with the appropriate name
     * Returns an empty QVariant if the option is not found.
     */
    QVariant getOption(const QString name);

    void setAvatarMapEntry(const qint64 id, const QString path);
    void setUnreadMapEntry(const qint64 id, const qint32 unread_count);
    void removeMapEntry(const qint64 id);
    void clearNotificationFor(const qint64 id);
    void shutDown();
    
signals:
    void authStateChanged(QTdAuthState *state);
    void connectionStateChanged(QTdConnectionState *state);
    void updateUser(QJsonObject user);
    void updateUserStatus(const QString &user_id, const QJsonObject &status);
    void updateUserFullInfo(const QString &user_id, const QJsonObject &fullInfo);
    void updateFile(const QJsonObject &file);
    void updateNewChat(const QJsonObject &chat);
    void updateChatPosition(const QJsonObject &chat);
    void updateChatLastMessage(const QJsonObject &chat);
    void updateChatActionBar(const QJsonObject &chat);
    void updateMessageSendStatus(const QJsonObject &chat);
    void updateMessageContent(const QJsonObject &chat);
    void updateBasicGroup(const QJsonObject &group);
    void updateBasicGroupFullInfo(const QJsonObject &group);
    void updateSecretChat(const QJsonObject &chat);
    void updateSuperGroup(const QJsonObject &group);
    void updateSupergroupFullInfo(const QJsonObject &group);
    void updateChatReadInbox(const QJsonObject &chat);
    void updateChatReadOutbox(const QJsonObject &chat);
    void updateChatPhoto(const QJsonObject &photo);
    void updateChatReplyMarkup(const QJsonObject &chat);
    void updateChatDraftMessage(const QJsonObject &chat);
    void updateChatTitle(const QJsonObject &chat);
    void updateChatUnreadMentionCount(const QJsonObject &chat);
    void updateChatAction(const QJsonObject &chat);
    void updateChatNotificationSettings(const QJsonObject &chat);
    void updateDeleteMessages(const QJsonObject &messages);
    void updateOption(const QJsonObject &option);
    void updateUnreadMessageCount(const QJsonObject &message);
    void updateScopeNotificationSettings(const QJsonObject &message);
    void updateMessageEdited(const QJsonObject &message);
    void updateUnreadChatCount(const QJsonObject &message);
    void updateNewMessage(const QJsonObject &message);
    void updateMessageInteractionInfo(const QJsonObject &message);
    void updateChatOnlineMemberCount(const QJsonObject &data);
    void updateFileGenerationStart(const QJsonObject &data);
    void updateFileGenerationStop(const QJsonObject &data);

    // Response signals
    void error(QJsonObject error);
    void ok(QJsonObject message);
    void chats(QJsonObject chats);
    void chat(QJsonObject chat);
    void basicGroup(QJsonObject group);
    void secretChat(QJsonObject chat);
    void superGroup(QJsonObject group);
    void supergroupFullInfo(QJsonObject group);
    void messages(QJsonObject messages);
    void message(QJsonObject message);
    void messageLink(QJsonObject messageLink);
    void file(QJsonObject file);
    void user(QJsonObject user);
    void users(QJsonObject users);
    void importedContacts(QJsonObject importedContacts);
    void userFullInfo(QJsonObject userFullInfo);
    void stickerSets(QJsonObject stickerSets);
    void stickerSet(QJsonObject stickerSet);
    void updateInstalledStickerSets(QJsonObject stickerSetsUpdate);
    void chatInviteLinkInfo(QJsonObject chatInviteLinkInfo);
    void pushReceiverId(QJsonObject);
    void proxies(QJsonObject);
    void proxy(QJsonObject);
    void seconds(QJsonObject);
    
private slots:
    void handleRecv(const QJsonObject &data);

private:
    Q_DISABLE_COPY(QTdClient)
    bool m_debug;
    void init();
    void handleUpdateOption(const QJsonObject &json);
    QScopedPointer<QThread> m_worker;
    QPointer<QTdAuthState> m_authState;
    QPointer<QTdConnectionState> m_connectionState;
    QHash<QString, ReceiveCallback> m_events;
    QHash<QString, QVariant> m_options;

    QString getTag();
    int m_tagcounter;
    AuxDatabase m_auxdb;
    PostalClient m_postalClient;
};

#endif // QTDCLIENT_H
