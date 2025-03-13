#include "qtdcreateprivatechatrequest.h"
#include "client/qtdclient.h"

QTdCreatePrivateChatRequest::QTdCreatePrivateChatRequest(QObject *parent)
    : QTdRequest(parent)
    , m_userId(0)
{
}

void QTdCreatePrivateChatRequest::setUserId(const qint64 &id)
{
    m_userId = id;
}

void QTdCreatePrivateChatRequest::setForce(const bool &force)
{
    m_force = force;
}

QJsonObject QTdCreatePrivateChatRequest::marshalJson()
{
  return QJsonObject{
      {"@type", "createPrivateChat"},
      {"user_id", m_userId},
      {"force", m_force}
  };
}

QFuture<QTdResponse> QTdCreatePrivateChatRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::chat);
}
