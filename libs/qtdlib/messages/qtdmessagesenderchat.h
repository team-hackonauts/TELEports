#ifndef QTDMESSAGESENDERCHAT_H
#define QTDMESSAGESENDERCHAT_H

#include "qtdmessagesender.h"
#include "chat/qtdchat.h"

/**
 * @brief The QTdMessageSenderChat class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_sender_chat.html
 */
class QTdMessageSenderChat : public QTdMessageSender
{
    Q_OBJECT
    Q_PROPERTY(QString smallPhotoPath READ smallPhotoPath NOTIFY chatChanged)

public:
    explicit QTdMessageSenderChat(QObject *parent = nullptr);

    QString displayName() const;
    QString fullName() const;
    QTdPhoto *photo() const;
    QString smallPhotoPath() const;
    QString initials() const;

    void unmarshalJson(const QJsonObject &json, const QString &id_key) override;
signals:
    void chatChanged();

private:
    Q_DISABLE_COPY(QTdMessageSenderChat)
    QTdChat *m_chat;
    bool m_waitingForChat;

    void updateChat(const qint64 &chatId);
};

#endif // QTDMESSAGESENDERCHAT_H
