#include "qtdauthstate.h"

QTdAuthStateWaitParams::QTdAuthStateWaitParams(QObject *parent)
    : QTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_WAIT_TDLIB_PARAMETERS);
}

QTdAuthStateWaitEncryptionKey::QTdAuthStateWaitEncryptionKey(QObject *parent)
    : QTdAuthState(parent)
    , m_encrypted(false)
{
    setType(AUTHORIZATION_STATE_WAIT_ENCRYPTION_KEY);
}

bool QTdAuthStateWaitEncryptionKey::isEncrypted() const
{
    return m_encrypted;
}

void QTdAuthStateWaitEncryptionKey::setIsEncrypted(const bool encrypted)
{
    if (encrypted != m_encrypted) {
        m_encrypted = encrypted;
        emit isEncryptedChanged(m_encrypted);
    }
}

void QTdAuthStateWaitEncryptionKey::unmarshalJson(const QJsonObject &json)
{
    QTdAuthState::unmarshalJson(json);
    if (json.contains("is_encrypted")) {
        setIsEncrypted(json["is_encrypted"].toBool());
    }
}

QTdAuthStateWaitRegistration::QTdAuthStateWaitRegistration(QObject *parent)
    : QTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_WAIT_REGISTRATION);
}

QTdAuthStateWaitPhoneNumber::QTdAuthStateWaitPhoneNumber(QObject *parent)
    : QTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_WAIT_PHONE_NUMBER);
}

QTdAuthStateWaitCode::QTdAuthStateWaitCode(QObject *parent)
    : QTdAuthState(parent)
    , m_info(0)
{
    setType(AUTHORIZATION_STATE_WAIT_CODE);
}

QTdAuthCodeInfo *QTdAuthStateWaitCode::info() const
{
    return m_info;
}

void QTdAuthStateWaitCode::unmarshalJson(const QJsonObject &json)
{
    QTdAuthState::unmarshalJson(json);
    m_info = new QTdAuthCodeInfo(this);
    m_info->unmarshalJson(json["code_info"].toObject());
    emit infoChanged();
}

QTdAuthStateWaitPassword::QTdAuthStateWaitPassword(QObject *parent)
    : QTdAuthState(parent)
    , m_hasRecovery(false)
{
    setType(AUTHORIZATION_STATE_WAIT_PASSWORD);
}

QString QTdAuthStateWaitPassword::passwordHint() const
{
    return m_hint;
}

QString QTdAuthStateWaitPassword::recoveryEmail() const
{
    return m_recovery;
}

bool QTdAuthStateWaitPassword::hasRecoveryEmail() const
{
    return m_hasRecovery;
}

void QTdAuthStateWaitPassword::unmarshalJson(const QJsonObject &json)
{
    QTdAuthState::unmarshalJson(json);
    m_hint = json["password_hint"].toString();
    m_recovery = json["recovery_email_address_pattern"].toString();
    m_hasRecovery = json["has_recovery_email_address"].toBool();
    emit dataChanged();
}

QTdAuthStateReady::QTdAuthStateReady(QObject *parent)
    : QTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_READY);
}

QTdAuthStateLoggingOut::QTdAuthStateLoggingOut(QObject *parent)
    : QTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_LOGGING_OUT);
}

QTdAuthStateClosing::QTdAuthStateClosing(QObject *parent)
    : QTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_CLOSING);
}

QTdAuthStateClosed::QTdAuthStateClosed(QObject *parent)
    : QTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_CLOSED);
}
