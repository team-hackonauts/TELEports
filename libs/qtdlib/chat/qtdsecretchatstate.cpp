#include "qtdsecretchatstate.h"

QTdSecretChatState::QTdSecretChatState(QObject *parent)
    : QTdObject(parent)
{
}

QTdSecretChatStateClosed::QTdSecretChatStateClosed(QObject *parent)
    : QTdSecretChatState(parent)
{
    setType(SECRET_CHAT_STATE_CLOSED);
}

QTdSecretChatStatePending::QTdSecretChatStatePending(QObject *parent)
    : QTdSecretChatState(parent)
{
    setType(SECRET_CHAT_STATE_PENDING);
}

QTdSecretChatStateReady::QTdSecretChatStateReady(QObject *parent)
    : QTdSecretChatState(parent)
{
    setType(SECRET_CHAT_STATE_READY);
}
