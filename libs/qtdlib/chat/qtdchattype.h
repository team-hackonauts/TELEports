#ifndef QTDCHATTYPE_H
#define QTDCHATTYPE_H

#include <QObject>
#include "common/qabstracttdobject.h"
#include "common/qtdint.h"
#include "user/qtduser.h"

/**
 * @brief The QTdChatType class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_chat_type.html
 */
class QTdChatType : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatType)
public:
    explicit QTdChatType(QObject *parent = nullptr);

};

/**
 * @brief The QTdChatTypeBasicGroup class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_type_basic_group.html
 */
class QTdChatTypeBasicGroup : public QTdChatType
{
    Q_OBJECT
    Q_PROPERTY(QString basicGroupId READ qmlBasicGroupId NOTIFY groupIdChanged)
public:
    explicit QTdChatTypeBasicGroup(QObject *parent = Q_NULLPTR);

    QString qmlBasicGroupId() const;
    qint64 basicGroupId() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void groupIdChanged();

private:
    Q_DISABLE_COPY(QTdChatTypeBasicGroup)
    QTdInt64 m_groupId;
};

/**
 * @brief The QTdChatTypePrivate class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_type_private.html
 */
class QTdChatTypePrivate : public QTdChatType
{
    Q_OBJECT
    Q_PROPERTY(QString userId READ qmlUserId NOTIFY userIdChanged)
    Q_PROPERTY(QTdUser *user READ user NOTIFY userChanged)
public:
    explicit QTdChatTypePrivate(QObject *parent = Q_NULLPTR);

    QString qmlUserId() const;
    qint64 userId() const;
    QTdUser *user() const;

    virtual void unmarshalJson(const QJsonObject &json) override;
    
signals:
    void userIdChanged();
    void userChanged();

private:
    Q_DISABLE_COPY(QTdChatTypePrivate)
    QTdInt64 m_userId;
    QTdUser *m_user;
    bool m_waitingForUser;

    void updateUser(const qint64 &userId);
};

/**
 * @brief The QTdChatTypeSecret class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_type_secret.html
 */
class QTdChatTypeSecret : public QTdChatTypePrivate
{
    Q_OBJECT
    Q_PROPERTY(QString secretChatId READ qmlSecretChatId NOTIFY secretChatIdChanged)
public:
    explicit QTdChatTypeSecret(QObject *parent = Q_NULLPTR);

    QString qmlSecretChatId() const;
    qint64 secretChatId() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void secretChatIdChanged();

private:
    Q_DISABLE_COPY(QTdChatTypeSecret)
    QTdInt64 m_chatId;
};

/**
 * @brief The QTdChatTypeSuperGroup class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_type_supergroup.html
 */
class QTdChatTypeSuperGroup : public QTdChatType
{
    Q_OBJECT
    Q_PROPERTY(QString superGroupId READ qmlSuperGroupId NOTIFY superGroupIdChanged)
    Q_PROPERTY(bool isChannel READ isChannel NOTIFY isChannelChanged)
public:
    explicit QTdChatTypeSuperGroup(QObject *parent = Q_NULLPTR);

    QString qmlSuperGroupId() const;
    qint64 superGroupId() const;
    bool isChannel() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void superGroupIdChanged();
    void isChannelChanged();

private:
    Q_DISABLE_COPY(QTdChatTypeSuperGroup)
    QTdInt64 m_groupId;
    bool m_isChannel;
};

#endif // QTDCHATTYPE_H
