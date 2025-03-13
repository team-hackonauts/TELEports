#include "common/qabstracttdobject.h"
#include "qtdmessageforwardorigin.h"
#include "common/qtdhelpers.h"
#include "user/qtdusers.h"
#include "user/qtduser.h"
#include "user/requests/qtdgetuserrequest.h"
#include "chat/qtdchatlistmodel.h"
#include "chat/qtdchat.h"
#include "chat/requests/qtdgetchatrequest.h"
#include "utils/await.h" 

QTdMessageForwardOrigin::QTdMessageForwardOrigin(QObject *parent)
    : QTdObject(parent)
{
}

QTdMessageForwardOriginChat::QTdMessageForwardOriginChat(QObject *parent)
    : QTdMessageForwardOrigin(parent)
    , m_senderChatId(0)
{
    setType(MESSAGE_FORWARD_ORIGIN_CHAT);
}

QString QTdMessageForwardOriginChat::originSummary() const
{
    return m_senderChatname;
}

QString QTdMessageForwardOriginChat::qmlChatId() const
{
    return m_senderChatId.toQmlValue();
}
qint64 QTdMessageForwardOriginChat::chatId() const
{
    return m_senderChatId.value();
}

QString QTdMessageForwardOriginChat::authorSignature() const
{
    return m_authorSignature;
}

void QTdMessageForwardOriginChat::unmarshalJson(const QJsonObject &json)
{
     QTdMessageForwardOrigin::unmarshalJson(json);
    if (json.isEmpty()) {
        return;
    }
    m_senderChatId = json["sender_chat_id"].toVariant().toLongLong();
    m_authorSignature = json["author_signature"].toString();

    auto *chat = QTdChatListModel::instance()->chatById(m_senderChatId.value());
    if (chat) {
        m_senderChatname = chat->title();
    } else {
        QScopedPointer<QTdGetChatRequest> req(new QTdGetChatRequest);
        req->setChatId(m_senderChatId.value());
        QFuture<QTdResponse> resp = req->sendAsync();
        await(resp);
        if (resp.result().isError()) {
            qWarning() << "QTdMessageForwardOriginChat::unmarshalJson Failed to get chat with error: " << resp.result().errorString();
            m_senderChatname = "";
        } else if (!resp.result().json().isEmpty()) {
            m_senderChatname = resp.result().json()["title"].toString();
        }
    }
    emit forwardOriginChanged();
}

QTdMessageForwardOriginChannel::QTdMessageForwardOriginChannel(QObject *parent)
    : QTdMessageForwardOrigin(parent)
    , m_chatId(0)
    , m_messageId(0)
{
    setType(MESSAGE_FORWARD_ORIGIN_CHANNEL);
}

QString QTdMessageForwardOriginChannel::originSummary() const
{
    return m_senderChannelname;
}

QString QTdMessageForwardOriginChannel::qmlChatId() const
{
    return m_chatId.toQmlValue();
}
qint64 QTdMessageForwardOriginChannel::chatId() const
{
    return m_chatId.value();
}

QString QTdMessageForwardOriginChannel::qmlMessageId() const
{
    return m_messageId.toQmlValue();
}
qint64 QTdMessageForwardOriginChannel::messageId() const
{
    return m_messageId.value();
}

QString QTdMessageForwardOriginChannel::authorSignature() const
{
    return m_authorSignature;
}

void QTdMessageForwardOriginChannel::unmarshalJson(const QJsonObject &json)
{
    QTdMessageForwardOrigin::unmarshalJson(json);
    if (json.isEmpty()) {
        return;
    }
    m_chatId = json["chat_id"].toVariant().toLongLong();
    m_messageId = json["message_id"].toVariant().toLongLong();
    m_authorSignature = json["author_signature"].toString();
    auto *chat = QTdChatListModel::instance()->chatById(m_chatId.value());
    if (chat) {
        m_senderChannelname = chat->title();
    } else {
        QScopedPointer<QTdGetChatRequest> req(new QTdGetChatRequest);
        req->setChatId(m_chatId.value());
        QFuture<QTdResponse> resp = req->sendAsync();
        await(resp);
        if (resp.result().isError()) {
            qWarning() << "QTdMessageForwardOriginChannel::unmarshalJson Failed to get channel with error: " << resp.result().errorString();
            m_senderChannelname = "";
        } else if (!resp.result().json().isEmpty()) {
            m_senderChannelname = resp.result().json()["title"].toString();
        }
    }
    emit forwardOriginChanged();
}

QTdMessageForwardOriginHiddenUser::QTdMessageForwardOriginHiddenUser(QObject *parent)
    : QTdMessageForwardOrigin(parent)
{
    setType(MESSAGE_FORWARD_ORIGIN_HIDDEN_USER);
}

QString QTdMessageForwardOriginHiddenUser::originSummary() const
{
    return senderName();
}

QString QTdMessageForwardOriginHiddenUser::senderName() const
{
    return m_senderName;
}

void QTdMessageForwardOriginHiddenUser::unmarshalJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    QTdMessageForwardOrigin::unmarshalJson(json);
    m_senderName = json["sender_name"].toString();
    emit forwardOriginChanged();
}

QTdMessageForwardOriginUser::QTdMessageForwardOriginUser(QObject *parent)
    : QTdMessageForwardOrigin(parent)
    , m_senderUserId(0)
{
    setType(MESSAGE_FORWARD_ORIGIN_USER);
}

QString QTdMessageForwardOriginUser::originSummary() const
{
    return m_senderUsername;
}

QString QTdMessageForwardOriginUser::qmlSenderUserId() const
{
    return m_senderUserId.toQmlValue();
}

qint64 QTdMessageForwardOriginUser::senderUserId() const
{
    return m_senderUserId.value();
}

void QTdMessageForwardOriginUser::unmarshalJson(const QJsonObject &json)
{
    QString firstName, lastName;

    if (json.isEmpty()) {
        return;
    }
    QTdMessageForwardOrigin::unmarshalJson(json);
    m_senderUserId = json["sender_user_id"].toVariant().toLongLong();
    auto *user = QTdUsers::instance()->model()->getByUid(QString::number(m_senderUserId.value()));
    if (user) {
        firstName = user->firstName();
        lastName = user->lastName();
    } else {
        QScopedPointer<QTdGetUserRequest> req(new QTdGetUserRequest);
        req->setUserId(m_senderUserId.value());
        QFuture<QTdResponse> resp = req->sendAsync();
        await(resp);
        if (resp.result().isError()) {
            qWarning() << "Failed to get user with error: " << resp.result().errorString();
        } else {
            auto tempUser = new QTdUser(this);
            tempUser->unmarshalJson(resp.result().json());
            firstName = tempUser->firstName();
            lastName = tempUser->lastName();
            delete tempUser;
        }
    }
    m_senderUsername = firstName;
    if (!lastName.isEmpty()) {
        m_senderUsername += " " + lastName;
    }
    emit forwardOriginChanged();
}
