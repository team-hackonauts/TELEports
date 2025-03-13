#include "qtdclient.h"
#include <QDebug>
#include <QPointer>
#include <QEventLoop>
#include <QMetaObject>
#include <QJsonDocument>
#include <QtConcurrent>
#include <QJsonDocument>
#include <QApplication>
#include <QStandardPaths>
#include "qtdthread.h"
#include "qtdhandle.h"
#include "auth/qtdauthstatefactory.h"
#include "requests/qtdcloserequest.h"
#include "connections/qtdconnectionstatefactory.h"
#include "../../common/auxdb/auxdb.h"
#include "../../common/auxdb/avatarmaptable.h"

QJsonObject execTd(const QJsonObject &json, const bool debug)
{
    if (debug)
        qDebug() << "[EXEC]" << json;
    const QByteArray tmp = (QJsonDocument(json).toJson(QJsonDocument::Compact) % '\0');
    QSharedPointer<Handle> tdlib = QTdHandle::instance();
    const QByteArray str = QByteArray(td_json_client_execute(tdlib->handle(), tmp.constData()));
    const QJsonObject ret = QJsonDocument::fromJson(str).object();
    if (debug)
        qDebug() << "[EXEC RESULT]" << ret;
    return ret;
}

void sendTd(const QJsonObject &json, const bool debug)
{
    if (debug)
        qDebug() << "[SEND] :" << json;
    const QByteArray msg = QJsonDocument(json).toJson(QJsonDocument::Compact).append('\0');
    QSharedPointer<Handle> tdlib = QTdHandle::instance();
    td_json_client_send(tdlib->handle(), msg.constData());
}

QTdClient::QTdClient(QObject *parent)
    : QObject(parent)
    , m_worker(new QThread)
    , m_authState(Q_NULLPTR)
    , m_connectionState(Q_NULLPTR)
    , m_tagcounter(0)
    , m_auxdb(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/auxdb"),
              QGuiApplication::applicationDirPath().append("/assets"), this)
    , m_postalClient("teleports.ubports_teleports")
    , m_debug(false)
{
    if (!m_debug) {
        m_debug = qgetenv("TDLIB_DEBUG") == QByteArrayLiteral("1");
    }

#ifdef TDLIB_DEBUG
    m_debug = true;
#endif

    m_auxdb.getAvatarMapTable()->resetUnreadMap();
    QThreadPool::globalInstance()->setMaxThreadCount(99);
    init();
    auto thread = m_worker.data();
    QTdWorker *worker = new QTdWorker();
    worker->moveToThread(thread);
    connect(worker, &QTdWorker::recv, this, &QTdClient::handleRecv);
    connect(this, &QTdClient::updateOption, this, &QTdClient::handleUpdateOption);

    connect(thread, &QThread::started, worker, &QTdWorker::run);
    connect(worker, &QTdWorker::finished, worker, &QTdWorker::deleteLater);
    connect(worker, &QTdWorker::destroyed, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    m_worker->start();
    qWarning() << "App Paths:" << QGuiApplication::applicationDirPath();
}

static QPointer<QTdClient> s_tdclient;
QTdClient *QTdClient::instance()
{
    if (s_tdclient.isNull()) {
        s_tdclient = new QTdClient();
    }
    return s_tdclient;
}

QTdAuthState *QTdClient::authState() const
{
    return m_authState;
}

QTdConnectionState *QTdClient::connectionState() const
{
    return m_connectionState;
}

void QTdClient::send(QTdRequest *obj)
{
    send(obj->marshalJson());
}

void QTdClient::send(const QJsonObject &json)
{
    if (json.isEmpty()) {
        qDebug() << "Empty Json object, nothing to send?";
        return;
    }
    QtConcurrent::run(sendTd, json, m_debug);
}

QFuture<QTdResponse> QTdClient::sendAsync(QTdRequest *obj, void (QTdClient::*signal)(QJsonObject))
{
    const QString tag = getTag();
    QJsonObject data = obj->marshalJson();
    data["@extra"] = tag;
    QFuture<QTdResponse> f = QtConcurrent::run([this](void (QTdClient::*s)(QJsonObject), const QJsonObject &data, const QString &tag) -> QTdResponse {
        // TODO: Should we wrap this up in a QRunnable instead of using an event loop
        QEventLoop loop;

        QTdResponse result;
        auto respSlot = [&](QJsonObject resp) {
            if (resp.contains("@extra")) {
                QString extra = resp.value("@extra").toString();
                if (extra == tag) {
                    result.setJson(resp);
                    if (result.isError()) {
                        qWarning() << "-------------[ SENDASYNC ERROR ]-----------------------";
                        qWarning() << result.errorString();
                        qWarning() << data;
                        qWarning() << "-------------------------------------------------------";
                    }
                    loop.quit();
                }
            }
        };

        QMetaObject::Connection con1 = QObject::connect(QTdClient::instance(), s, respSlot);
        QMetaObject::Connection con2 = QObject::connect(QTdClient::instance(), &QTdClient::error, respSlot);

        /**
         * We send the data from within the thread due to how QtConcurrent allocates
         * one thread per cpu core. Which we don't want to start up the response loop and it
         * take up the last remaining thread and then no request is actually sent.
         *
         * This ensures that if we are either in the last available thread or waiting
         * for the next available thread the request is always sent "after" setting up the response
         * slots.
         */
        sendTd(data, m_debug);

        loop.exec();
        disconnect(con1);
        disconnect(con2);
        return result;
    },
                                               signal, data, tag);
    return f;
}

QFuture<QJsonObject> QTdClient::exec(QTdRequest *obj)
{
    return exec(obj->marshalJson());
}

QFuture<QJsonObject> QTdClient::exec(const QJsonObject &json)
{
    return QtConcurrent::run(execTd, json, m_debug);
}

void QTdClient::handleRecv(const QJsonObject &data)
{
    const QString type = data["@type"].toString();

    if (m_debug) {
        qDebug() << "-------------[ RCV ]-----------------------";
        qDebug() << "TYPE >> " << type;
        qDebug() << "DATA >> " << data;
        qDebug() << "-------------------------------------------";
    } else if (type == "error") {
        qWarning() << "-------------[ RCV ERROR ]-----------------------";
        qWarning() << "TYPE >> " << type;
        qWarning() << "DATA >> " << data;
        qWarning() << "-------------------------------------------------";
    }

    if (m_events.contains(type)) {
        m_events.value(type)(data);
        return;
    }
    qWarning() << "---------[UNHANDLED]-------------";
    qWarning() << type;
    qWarning() << "---------------------------------";
}

void QTdClient::init()
{
    m_events.insert(QStringLiteral("updateAuthorizationState"), [=](const QJsonObject &data) {
        QTdAuthState *state = QTdAuthStateFactory::create(data, this);
        if (!state) {
            qDebug() << "Unknown auth state: " << data;
            return;
        }
        if (!m_authState || (state->type() != m_authState->type())) {
            if (m_authState) {
                delete m_authState;
                m_authState = 0;
            }
            m_authState = state;
            emit authStateChanged(m_authState);
        }
    });

    m_events.insert(QStringLiteral("updateConnectionState"), [=](const QJsonObject &data) {
        if (m_connectionState) {
            delete m_connectionState;
            m_connectionState = 0;
        }
        m_connectionState = QTdConnectionStateFactory::create(data, this);
        emit connectionStateChanged(m_connectionState);
    });

    m_events.insert(QStringLiteral("updateUser"), [=](const QJsonObject &data) {
        emit updateUser(data["user"].toObject());
    });
    m_events.insert(QStringLiteral("updateUserFullInfo"), [=](const QJsonObject &data) {
        const QString userId = data["user_id"].toVariant().toString();
        emit updateUserFullInfo(userId, data["user_full_info"].toObject());
    });
    m_events.insert(QStringLiteral("updateUserStatus"), [=](const QJsonObject &data) {
        const QString userId = data["user_id"].toVariant().toString();
        emit updateUserStatus(userId, data["status"].toObject());
    });

    m_events.insert(QStringLiteral("updateFile"), [=](const QJsonObject &data) {
        emit updateFile(data["file"].toObject());
    });

    m_events.insert(QStringLiteral("updateNewChat"), [=](const QJsonObject &data) {
        emit updateNewChat(data["chat"].toObject());
    });

    m_events.insert(QStringLiteral("updateBasicGroup"), [=](const QJsonObject &data) {
        emit updateBasicGroup(data["basic_group"].toObject());
    });

    m_events.insert(QStringLiteral("updateBasicGroupFullInfo"), [=](const QJsonObject &data) {
        emit updateBasicGroupFullInfo(data);
    });
    m_events.insert(QStringLiteral("basicGroup"), [=](const QJsonObject &data) { emit updateBasicGroup(data); });
    m_events.insert(QStringLiteral("secretChat"), [=](const QJsonObject &data) { emit secretChat(data); });
    m_events.insert(QStringLiteral("updateSecretChat"), [=](const QJsonObject &data) { emit updateSecretChat(data["secret_chat"].toObject()); });
    m_events.insert(QStringLiteral("supergroup"), [=](const QJsonObject &data) { emit superGroup(data); });
    m_events.insert(QStringLiteral("updateSupergroupFullInfo"), [=](const QJsonObject &data) { emit updateSupergroupFullInfo(data); });
    m_events.insert(QStringLiteral("supergroupFullInfo"), [=](const QJsonObject &data) { emit supergroupFullInfo(data); });
    m_events.insert(QStringLiteral("updateSupergroup"), [=](const QJsonObject &data) { emit updateSuperGroup(data["supergroup"].toObject()); });
    m_events.insert(QStringLiteral("updateChatPosition"), [=](const QJsonObject &data) { emit updateChatPosition(data); });
    m_events.insert(QStringLiteral("updateChatLastMessage"), [=](const QJsonObject &data) { emit updateChatLastMessage(data); });
    m_events.insert(QStringLiteral("updateMessageContent"), [=](const QJsonObject &data) { emit updateMessageContent(data); });
    m_events.insert(QStringLiteral("updateMessageSendSucceeded"), [=](const QJsonObject &data) { emit updateMessageSendStatus(data); });
    m_events.insert(QStringLiteral("updateMessageSendFailed"), [=](const QJsonObject &data) { emit updateMessageSendStatus(data); });
    m_events.insert(QStringLiteral("updateChatReadInbox"), [=](const QJsonObject &data) { emit updateChatReadInbox(data); });
    m_events.insert(QStringLiteral("updateChatPhoto"), [=](const QJsonObject &data) { emit updateChatPhoto(data); });
    m_events.insert(QStringLiteral("updateChatReadOutbox"), [=](const QJsonObject &data) { emit updateChatReadOutbox(data); });
    m_events.insert(QStringLiteral("updateChatReplyMarkup"), [=](const QJsonObject &data) { emit updateChatReplyMarkup(data); });
    m_events.insert(QStringLiteral("updateChatDraftMessage"), [=](const QJsonObject &data) { emit updateChatDraftMessage(data); });
    m_events.insert(QStringLiteral("updateChatTitle"), [=](const QJsonObject &data) { emit updateChatTitle(data); });
    m_events.insert(QStringLiteral("updateChatUnreadMentionCount"), [=](const QJsonObject &data) { emit updateChatUnreadMentionCount(data); });
    m_events.insert(QStringLiteral("updateMessageMentionRead"), [=](const QJsonObject &data) { emit updateChatUnreadMentionCount(data); });

    m_events.insert(QStringLiteral("updateUnreadMessageCount"), [=](const QJsonObject &data) { emit updateUnreadMessageCount(data); });
    m_events.insert(QStringLiteral("updateScopeNotificationSettings"), [=](const QJsonObject &data) { emit updateScopeNotificationSettings(data); });
    m_events.insert(QStringLiteral("updateUnreadChatCount"), [=](const QJsonObject &data) { emit updateUnreadChatCount(data); });
    m_events.insert(QStringLiteral("updateMessageEdited"), [=](const QJsonObject &data) { emit updateMessageEdited(data); });
    m_events.insert(QStringLiteral("updateDeleteMessages"), [=](const QJsonObject &data) { emit updateDeleteMessages(data); });

    m_events.insert(QStringLiteral("updateChatAction"), [=](const QJsonObject &data) { emit updateChatAction(data); });
    m_events.insert(QStringLiteral("updateChatActionBar"), [=](const QJsonObject &data) { emit updateChatActionBar(data); });
    
    m_events.insert(QStringLiteral("updateChatNotificationSettings"), [=](const QJsonObject &data) { emit updateChatNotificationSettings(data); });
    m_events.insert(QStringLiteral("updateChatOnlineMemberCount"), [=](const QJsonObject &data) { emit updateChatOnlineMemberCount(data); });

    m_events.insert(QStringLiteral("updateFileGenerationStart"), [=](const QJsonObject &data) { emit updateFileGenerationStart(data); });
    m_events.insert(QStringLiteral("updateFileGenerationStop"), [=](const QJsonObject &data) { emit updateFileGenerationStop(data); });

    m_events.insert(QStringLiteral("messages"), [=](const QJsonObject &data) { emit messages(data); });
    m_events.insert(QStringLiteral("message"), [=](const QJsonObject &data) { emit message(data); });
    m_events.insert(QStringLiteral("messageLink"), [=](const QJsonObject &data) { emit messageLink(data); });

    //Option handling - more or less global constants, still could change during execution
    m_events.insert(QStringLiteral("updateOption"), [=](const QJsonObject &data) { emit updateOption(data); });

    m_events.insert(QStringLiteral("pushReceiverId"), [=](const QJsonObject &data) { emit pushReceiverId(data); });
    //Message updates to add to existing chats or channel views
    m_events.insert(QStringLiteral("updateNewMessage"), [=](const QJsonObject &data) { emit updateNewMessage(data); });
    m_events.insert(QStringLiteral("updateMessageInteractionInfo"), [=](const QJsonObject &data) { emit updateMessageInteractionInfo(data); });
    m_events.insert(QStringLiteral("chats"), [=](const QJsonObject &data) { emit chats(data); });
    m_events.insert(QStringLiteral("chat"), [=](const QJsonObject &data) { emit chat(data); });
    m_events.insert(QStringLiteral("error"), [=](const QJsonObject &data) { emit error(data); });
    m_events.insert(QStringLiteral("ok"), [=](const QJsonObject &data) { emit ok(data); });
    m_events.insert(QStringLiteral("basicGroup"), [=](const QJsonObject &group) { emit basicGroup(group); });
    m_events.insert(QStringLiteral("file"), [=](const QJsonObject &data) {
        emit updateFile(data);
        emit file(data);
    });
    m_events.insert(QStringLiteral("user"), [=](const QJsonObject &data) {
        emit updateUser(data);
        emit user(data);
    });
    m_events.insert(QStringLiteral("users"), [=](const QJsonObject &data) {
        emit users(data);
    });
    m_events.insert(QStringLiteral("proxies"), [=](const QJsonObject &data) {
        emit proxies(data);
    });
    m_events.insert(QStringLiteral("proxy"), [=](const QJsonObject &data) {
        emit proxy(data);
    });
        m_events.insert(QStringLiteral("seconds"), [=](const QJsonObject &data) {
        emit seconds(data);
    });
    m_events.insert(QStringLiteral("importedContacts"), [=](const QJsonObject &data) {
        emit importedContacts(data);
    });
    m_events.insert(QStringLiteral("userFullInfo"), [=](const QJsonObject &data) {
        emit userFullInfo(data);
    });
    m_events.insert(QStringLiteral("stickerSets"), [=](const QJsonObject &data) {
        emit stickerSets(data);
    });
    m_events.insert(QStringLiteral("stickerSet"), [=](const QJsonObject &data) {
        emit stickerSet(data);
    });
    m_events.insert(QStringLiteral("updateInstalledStickerSets"), [=](const QJsonObject &data) {
        emit updateInstalledStickerSets(data);
    });
    m_events.insert(QStringLiteral("chatInviteLinkInfo"), [=](const QJsonObject &data) {
        emit chatInviteLinkInfo(data);
    });
}

void QTdClient::handleUpdateOption(const QJsonObject &json)
{
    QString option_name = json["name"].toString();
    auto option_value = QVariant();
    auto value_obj = json["value"].toObject();
    auto type = value_obj["@type"].toString();
    if (type == "optionValueString") {
        option_value = value_obj["value"].toString();
    } else if (type == "optionValueInteger") {
        option_value = value_obj["value"].toVariant().toLongLong();
    } else if (type == "optionValueBoolean") {
        option_value = value_obj["value"].toBool();
    } else if (type == "optionValueEmpty") {
        option_value.clear();
    } else {
        qWarning() << "Unknown option type: " << type;
    }
    m_options[option_name] = option_value;
    qWarning() << "received option" << option_name << ", value" << option_value;
}

QString QTdClient::getTag()
{
    m_tagcounter++;
    return QString("req-%1").arg(QString::number(m_tagcounter));
}

QVariant QTdClient::getOption(const QString name)
{
    if (m_options.contains(name)) {
        return m_options[name];
    } else
        return QVariant();
}

void QTdClient::setAvatarMapEntry(const qint64 id, const QString path)
{
    if (path != "")
        m_auxdb.getAvatarMapTable()->setMapEntry(id, path);
}

void QTdClient::removeMapEntry(const qint64 id)
{
    m_auxdb.getAvatarMapTable()->removeMapEntry(id);
    m_postalClient.setCount(m_auxdb.getAvatarMapTable()->getTotalUnread());
}

void QTdClient::setUnreadMapEntry(const qint64 id, const qint32 unread_count)
{
    m_auxdb.getAvatarMapTable()->setUnreadMapEntry(id, unread_count);
    m_postalClient.setCount(m_auxdb.getAvatarMapTable()->getTotalUnread());
}

void QTdClient::clearNotificationFor(const qint64 id) {
    QStringList tags;
    tags = QStringList(QString::number(id));
    m_postalClient.clearPersistent(tags);
}

void QTdClient::shutDown()
{
    QScopedPointer<QTdCloseRequest> req(new QTdCloseRequest);
    req->sendAsync();
    while (m_authState->type() != QTdAuthState::Type::AUTHORIZATION_STATE_CLOSED)
    {
        QCoreApplication::processEvents();
    }
}
