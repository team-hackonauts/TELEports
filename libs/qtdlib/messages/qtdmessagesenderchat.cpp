#include "qtdmessagesenderchat.h"
#include "client/qtdclient.h"
#include "chat/qtdchatlistmodel.h"
#include "utils/debug.h"

QTdMessageSenderChat::QTdMessageSenderChat(QObject *parent)
    : QTdMessageSender(parent)
{
    setType(MESSAGE_SENDER_CHAT);
}

void QTdMessageSenderChat::unmarshalJson(const QJsonObject &json, const QString &id_key)
{
    QTdMessageSender::unmarshalJson(json, "chat_id");
    updateChat(id());
}

void QTdMessageSenderChat::updateChat(const qint64 &chatId)
{
    if (chatId != id()) {
        return;
    }
    if (m_chat) {
        m_chat = nullptr;
    }

    auto *chats = QTdChatListModel::instance();
    m_chat = chats->chatById(chatId);
    if (m_chat) {
        emit chatChanged();
        emit dataChanged();
        if (m_waitingForChat) {
            disconnect(QTdChatListModel::instance(), &QTdChatListModel::chatCreated, this, &QTdMessageSenderChat::updateChat);
            m_waitingForChat = false;
        }
        return;
    }
    connect(QTdChatListModel::instance(), &QTdChatListModel::chatCreated, this, &QTdMessageSenderChat::updateChat);
    QTdClient::instance()->send(QJsonObject {
            { "@type", "getChat" },
            { "chat_id", chatId } });
    m_waitingForChat = true;
}

QString QTdMessageSenderChat::displayName() const
{
    if (!m_chat) {
        return QString();
    }

    return m_chat->title();
}

QString QTdMessageSenderChat::fullName() const
{
    return displayName();
}

QTdPhoto *QTdMessageSenderChat::photo() const
{
    if (!m_chat) {
        return nullptr;
    }

    return m_chat->chatPhoto();
}

QString QTdMessageSenderChat::initials() const
{
    if (!m_chat) {
        return QString();
    }

    return m_chat->initials();
}

QString QTdMessageSenderChat::smallPhotoPath() const {
    return photo()->smallPhotoPath();
}
