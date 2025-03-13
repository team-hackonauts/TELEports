#include "qtdclosesecretchatrequest.h"

QTdCloseSecretChatRequest::QTdCloseSecretChatRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_secretChatId(0)
{
}

void QTdCloseSecretChatRequest::setSecretChatId(const qint64 &id)
{
    m_secretChatId = id;
}

QJsonObject QTdCloseSecretChatRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "closeSecretChat" },
        { "secret_chat_id", m_secretChatId }
    };
}
