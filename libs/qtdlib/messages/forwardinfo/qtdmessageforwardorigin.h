#ifndef QTDMESSAGEFORWARDORIGIN_H
#define QTDMESSAGEFORWARDORIGIN_H

#include "common/qabstractint64id.h"

/**
 * @brief The QTdMessageForwardOrigin class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_message_forward_origin.html
 */
class QTdMessageForwardOrigin : public QTdObject
{
    Q_OBJECT
    // Q_DISABLE_COPY(QTdMessageForwardOrigin)
    Q_PROPERTY(QString originSummary READ originSummary NOTIFY forwardOriginChanged)
public:
    explicit QTdMessageForwardOrigin(QObject *parent = nullptr);
    virtual QString originSummary() const = 0;

signals:
    void forwardOriginChanged();
};

/**
     * @brief The QTdMessageForwardOriginChat class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_origin_chat.html
 */
class QTdMessageForwardOriginChat : public QTdMessageForwardOrigin
{
    Q_OBJECT
    // Q_DISABLE_COPY(QTdMessageForwardOriginChat)

public:
    explicit QTdMessageForwardOriginChat(QObject *parent = nullptr);

    QString originSummary() const;
    QString qmlChatId() const;
    qint64 chatId() const;
    QString authorSignature() const;

    void unmarshalJson(const QJsonObject &json) override;

private:
    QTdInt64 m_senderChatId;
    QString m_authorSignature;
    QString m_senderChatname;
};

/**
     * @brief The QTdMessageForwardOriginChannel class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_origin_channel.html
 */
class QTdMessageForwardOriginChannel : public QTdMessageForwardOrigin
{
    Q_OBJECT
    // Q_DISABLE_COPY(QTdMessageForwardOriginChannel)

public:
    explicit QTdMessageForwardOriginChannel(QObject *parent = nullptr);

    QString originSummary() const;
    QString qmlChatId() const;
    qint64 chatId() const;
    QString qmlMessageId() const;
    qint64 messageId() const;
    QString authorSignature() const;

    void unmarshalJson(const QJsonObject &json) override;

private:
    QTdInt64 m_chatId;
    QTdInt64 m_messageId;
    QString m_authorSignature;
    QString m_senderChannelname;
};

/**
 * @brief The QTdMessageForwardOriginHiddenUser class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_origin_hidden_user.html
 */
class QTdMessageForwardOriginHiddenUser : public QTdMessageForwardOrigin
{
    Q_OBJECT
    // Q_DISABLE_COPY(QTdMessageForwardOriginHiddenUser)

public:
    explicit QTdMessageForwardOriginHiddenUser(QObject *parent = nullptr);

    QString originSummary() const;
    QString senderName() const;

    void unmarshalJson(const QJsonObject &json) override;

private:
    QString m_senderName;
};

/**
 * @brief The QTdMessageForwardOriginUser class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_origin_user.html
 */
class QTdMessageForwardOriginUser : public QTdMessageForwardOrigin
{
    Q_OBJECT
    // Q_DISABLE_COPY(QTdMessageForwardOriginUser)

public:
    explicit QTdMessageForwardOriginUser(QObject *parent = nullptr);

    QString originSummary() const;
    QString qmlSenderUserId() const;
    qint64 senderUserId() const;

    void unmarshalJson(const QJsonObject &json) override;

private:
    QTdInt64 m_senderUserId;
    QString m_senderUsername;
};

#endif // QTDMESSAGEFORWARDORIGIN_H
