#ifndef QTDAUTHSTATE_H
#define QTDAUTHSTATE_H

#include <QObject>
#include "common/qabstracttdobject.h"
#include "qtdauthcode.h"

/**
 * @brief The QTdAuthState class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_authorization_state.html
 */
class QTdAuthState : public QTdObject
{
    Q_OBJECT
public:
    explicit QTdAuthState(QObject *parent = Q_NULLPTR)
        : QTdObject(parent)
    {
    }
};

/**
 * @brief The QTdAuthStateWaitParams class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_tdlib_parameters.html
 */
class QTdAuthStateWaitParams : public QTdAuthState
{
    Q_OBJECT
public:
    explicit QTdAuthStateWaitParams(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdAuthStateWaitEncryptionKey class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_encryption_key.html
 */
class QTdAuthStateWaitEncryptionKey : public QTdAuthState
{
    Q_OBJECT
    Q_PROPERTY(bool isEncrypted READ isEncrypted NOTIFY isEncryptedChanged)
public:
    explicit QTdAuthStateWaitEncryptionKey(QObject *parent = Q_NULLPTR);

    bool isEncrypted() const;

signals:
    void isEncryptedChanged(bool encrypted);

protected:
    void setIsEncrypted(const bool encrypted);

private:
    bool m_encrypted;

    // QAbstractTdObject interface
public:
    void unmarshalJson(const QJsonObject &json) override;
};

/**
 * @brief The QTdAuthStateWaitRegistration class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_registration.html
 */
class QTdAuthStateWaitRegistration : public QTdAuthState
{
    Q_OBJECT
    // TODO termsOfService
public:
    explicit QTdAuthStateWaitRegistration(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdAuthStateWaitPhoneNumber class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_phone_number.html
 */
class QTdAuthStateWaitPhoneNumber : public QTdAuthState
{
    Q_OBJECT
public:
    explicit QTdAuthStateWaitPhoneNumber(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdAuthStateWaitCode class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_code.html
 */
class QTdAuthStateWaitCode : public QTdAuthState
{
    Q_OBJECT
    Q_PROPERTY(QTdAuthCodeInfo *info READ info NOTIFY infoChanged)
public:
    explicit QTdAuthStateWaitCode(QObject *parent = Q_NULLPTR);

    QTdAuthCodeInfo *info() const;
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void infoChanged();
    void isRegisteredChanged();

private:
    bool m_isRegistered;
    QTdAuthCodeInfo *m_info;
};

/**
 * @brief The QTdAuthStateWaitPassword class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_password.html
 */
class QTdAuthStateWaitPassword : public QTdAuthState
{
    Q_OBJECT
    Q_PROPERTY(QString passwordHint READ passwordHint NOTIFY dataChanged)
    Q_PROPERTY(bool hasRecoveryEmail READ hasRecoveryEmail NOTIFY dataChanged)
    Q_PROPERTY(QString recoveryEmail READ recoveryEmail NOTIFY dataChanged)
public:
    explicit QTdAuthStateWaitPassword(QObject *parent = Q_NULLPTR);

    QString passwordHint() const;
    QString recoveryEmail() const;
    bool hasRecoveryEmail() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void dataChanged();

private:
    QString m_hint;
    bool m_hasRecovery;
    QString m_recovery;
};

/**
 * @brief The QTdAuthStateReady class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_ready.html
 */
class QTdAuthStateReady : public QTdAuthState
{
    Q_OBJECT
public:
    explicit QTdAuthStateReady(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdAuthStateLoggingOut class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_logging_out.html
 */
class QTdAuthStateLoggingOut : public QTdAuthState
{
    Q_OBJECT
public:
    explicit QTdAuthStateLoggingOut(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdAuthStateClosing class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_closing.html
 */
class QTdAuthStateClosing : public QTdAuthState
{
    Q_OBJECT
public:
    explicit QTdAuthStateClosing(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdAuthStateClosed class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_closed.html
 */
class QTdAuthStateClosed : public QTdAuthState
{
    Q_OBJECT
public:
    explicit QTdAuthStateClosed(QObject *parent = Q_NULLPTR);
};

#endif // QTDAUTHSTATE_H
