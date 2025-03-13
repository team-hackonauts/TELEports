#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include "qtdauthstate.h"
#include "qtdauthparams.h"

class QTdAuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QTdAuthState *type READ type NOTIFY stateChanged)
    Q_PROPERTY(QTdAuthParams *params READ params WRITE setParams NOTIFY paramsChanged)
public:
    explicit QTdAuthManager(QObject *parent = nullptr);

    enum State {
        Invalid,
        WaitTdParams,
        WaitEncryptionKey,
        WaitRegistration,
        WaitPhoneNumber,
        WaitCode,
        WaitPassword,
        Ready,
        LoggingOut,
        Closing,
        Closed
    };
    Q_ENUM(State)
    State state() const;
    QTdAuthState *type() const;

    QTdAuthParams *params() const;

public slots:
    void setParams(QTdAuthParams *params);
    void sendParams();
    void setEncryptionKey(const QString &key);
    void sendPhoneNumber(const QString &number);
    void sendCode(const QString &code);
    void resendCode();
    void registerUser(const QString &firstname, const QString &lastname = "");
    void sendPassword(const QString &password);
    void shutDown();
    void logOut();
    void deleteAccount(const QString &reason);

signals:
    void stateChanged(State state);
    void waitingForTdParams();
    void waitingForEncryptionKey();
    void waitingForRegistration();
    void waitingForPhoneNumber();
    void waitingForCode(QTdAuthCode *type, QTdAuthCode *nextType, qint32 resendTimeout);
    void waitingForPassword(QString passwordHint, bool hasRecoveryEmailAddress, QString recoveryEmailAddressPattern);
    void phoneNumberError(QString message);
    void codeError(QString message);
    void passwordError(QString message);
    void ready();
    void loggingOut();
    void closing();
    void closed();

    void paramsChanged(QTdAuthParams *params);

private slots:
    void handleAuthStateChanged(QTdAuthState *state);

private:
    State m_state;
    QTdAuthParams *m_params;
};

#endif // AUTHMANAGER_H
