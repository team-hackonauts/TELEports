#include "qtdauthmanager.h"
#include <QDebug>
#include <QScopedPointer>
#include "client/qtdclient.h"
#include "requests/qtdauthencryptionkeyresponse.h"
#include "requests/qtdauthparametersresponse.h"
#include "requests/qtdauthphonenumberresponse.h"
#include "requests/qtdauthcoderesponse.h"
#include "requests/qtdauthregistrationresponse.h"
#include "requests/qtdauthlogoutresponse.h"
#include "requests/qtdauthpasswordresponse.h"
#include "requests/qtdauthdeleteaccountresponse.h"
#include "requests/qtdauthresendcoderequest.h"

#include "utils/await.h"

QTdAuthManager::QTdAuthManager(QObject *parent)
    : QObject(parent)
    , m_state(Invalid)
    , m_params(0)
{
    connect(QTdClient::instance(),
            &QTdClient::authStateChanged,
            this,
            &QTdAuthManager::handleAuthStateChanged);

    // Manually run the update now as the client may already be initialized
    // so we want the *current* state to set us up correctly.
    if (QTdClient::instance()->authState()) {
        handleAuthStateChanged(QTdClient::instance()->authState());
    }
}

QTdAuthManager::State QTdAuthManager::state() const
{
    return m_state;
}

QTdAuthState *QTdAuthManager::type() const
{
    return QTdClient::instance()->authState();
}

QTdAuthParams *QTdAuthManager::params() const
{
    return m_params;
}

void QTdAuthManager::setParams(QTdAuthParams *params)
{
    if (m_params == params)
        return;

    m_params = params;
    emit paramsChanged(m_params);
}

void QTdAuthManager::sendParams()
{
    if (!m_params) {
        qWarning() << "Missing auth params. aborting...";
        return;
    }

    if (m_state != WaitTdParams) {
        qWarning() << "TDLib isn't waiting for this so not sending!";
        return;
    }
    QScopedPointer<QTdAuthParametersResponse> resp(new QTdAuthParametersResponse);
    resp->setParameters(m_params);
    QTdClient::instance()->send(resp.data());
}

void QTdAuthManager::setEncryptionKey(const QString &key)
{
    if (m_state != WaitEncryptionKey) {
        qWarning() << "TDLib isn't waiting for the encryption key";
        return;
    }
    QScopedPointer<QTdAuthEncryptionKeyResponse> resp(new QTdAuthEncryptionKeyResponse);
    resp->setKey(key);
    QTdClient::instance()->send(resp.data());
}

void QTdAuthManager::sendPhoneNumber(const QString &number)
{
    if (m_state != WaitPhoneNumber) {
        qWarning() << "TDLib isn't waiting for the phone number";
        return;
    }
    QScopedPointer<QTdAuthPhoneNumberResponse> autPhoneNoResp(new QTdAuthPhoneNumberResponse);
    autPhoneNoResp->setPhoneNumber(number);
    QFuture<QTdResponse> resp = autPhoneNoResp->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        emit phoneNumberError(resp.result().errorString());
        return;
    }
}

void QTdAuthManager::shutDown()
{
    QTdClient::instance()->shutDown();
}

void QTdAuthManager::logOut()
{
    QScopedPointer<QTdAuthLogOutResponse> resp(new QTdAuthLogOutResponse);
    QTdClient::instance()->send(resp.data());
}

void QTdAuthManager::deleteAccount(const QString &reason)
{
    QScopedPointer<QTdAuthDeleteAccountResponse> resp(new QTdAuthDeleteAccountResponse);
    resp->setReason(reason);
    qWarning() << "Account deletion is disabled!";
    //QTdClient::instance()->send(resp.data());
}

void QTdAuthManager::sendCode(const QString &code)
{
    if (m_state != WaitCode) {
        qWarning() << "TDLib isn't waiting for a code";
        return;
    }
    QScopedPointer<QTdAuthCodeResponse> authCodeResp(new QTdAuthCodeResponse);
    authCodeResp->setCode(code);
    QFuture<QTdResponse> resp = authCodeResp->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        emit codeError(resp.result().errorString());
        return;
    }
}

void QTdAuthManager::resendCode()
{
    if (m_state != WaitCode) {
        qWarning() << "TDLib isn't waiting for a code";
        return;
    }
    QScopedPointer<QTdAuthResendCodeRequest> authResendCodeReq(new QTdAuthResendCodeRequest);
    QFuture<QTdResponse> resp = authResendCodeReq->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        emit codeError(resp.result().errorString());
        return;
    }
}

void QTdAuthManager::registerUser(const QString &firstname, const QString &lastname)
{
    if (m_state != WaitRegistration) {
        qWarning() << "TDLib isn't waiting for registration";
        return;
    }
    QScopedPointer<QTdAuthRegistrationResponse> authRegistrationResp(new QTdAuthRegistrationResponse);
    authRegistrationResp->setFirstName(firstname);
    authRegistrationResp->setLastName(lastname);
    QFuture<QTdResponse> resp = authRegistrationResp->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        emit codeError(resp.result().errorString());
        return;
    }
}

void QTdAuthManager::sendPassword(const QString &password)
{
    if (m_state != WaitPassword) {
        qWarning() << "TDLib isn't waiting for a password";
        return;
    }
    QScopedPointer<QTdAuthPasswordResponse> authPasswordResp(new QTdAuthPasswordResponse);
    authPasswordResp->setPassword(password);
    QFuture<QTdResponse> resp = authPasswordResp->sendAsync();
    await(resp);
    if (resp.result().isError()) {
        emit passwordError(resp.result().errorString());
        return;
    }
}

void QTdAuthManager::handleAuthStateChanged(QTdAuthState *state)
{
    if (!state)
        return;
    switch (state->type()) {
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_TDLIB_PARAMETERS: {
        m_state = WaitTdParams;
        emit waitingForTdParams();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_ENCRYPTION_KEY: {
        m_state = WaitEncryptionKey;
        emit waitingForEncryptionKey();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_REGISTRATION: {
        m_state = WaitRegistration;
        emit waitingForRegistration();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_PHONE_NUMBER: {
        m_state = WaitPhoneNumber;
        emit waitingForPhoneNumber();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_CODE: {
        auto currentState = (QTdAuthStateWaitCode *)state;
        emit waitingForCode(currentState->info()->type(), currentState->info()->nextType(), currentState->info()->timeout());
        m_state = WaitCode;
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_PASSWORD: {
        m_state = WaitPassword;
        auto currentState = (QTdAuthStateWaitPassword *)state;
        emit waitingForPassword(currentState->passwordHint(), currentState->hasRecoveryEmail(), currentState->recoveryEmail());
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_READY: {
        m_state = Ready;
        emit ready();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_LOGGING_OUT: {
        m_state = LoggingOut;
        emit loggingOut();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_CLOSING: {
        m_state = Closing;
        emit closing();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_CLOSED: {
        m_state = Closed;
        emit closed();
        QCoreApplication::quit();
        break;
    }
    default:
        return;
    }
    emit stateChanged(m_state);
}
