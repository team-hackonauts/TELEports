#include "qtdcreatenewsecretchatrequest.h"
#include "client/qtdclient.h"

QTdCreateNewSecretChatRequest::QTdCreateNewSecretChatRequest(QObject *parent)
    : QTdRequest(parent)
    , m_userId(0)
{
}

void QTdCreateNewSecretChatRequest::setUserId(const qint64 &id)
{
    m_userId = id;
}

QJsonObject QTdCreateNewSecretChatRequest::marshalJson()
{
  return QJsonObject{
      {"@type", "createNewSecretChat"},
      {"user_id", m_userId}
  };
}

QFuture<QTdResponse> QTdCreateNewSecretChatRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::chat);
}
