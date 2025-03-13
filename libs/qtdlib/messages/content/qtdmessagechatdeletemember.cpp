#include "qtdmessagechatdeletemember.h"
#include <QScopedPointer>
#include "user/requests/qtdgetuserrequest.h"
#include "utils/await.h"
#include "utils/i18n.h"

QTdMessageChatDeleteMember::QTdMessageChatDeleteMember(QObject *parent)
    : QTdMessageContent(parent)
    , m_user(Q_NULLPTR)
{
    setType(MESSAGE_CHAT_DELETE_MEMBER);
    connect(&m_watcher, &QFutureWatcher<QTdResponse>::finished, this, &QTdMessageChatDeleteMember::handleResponse);
}

QTdUser *QTdMessageChatDeleteMember::user() const
{
    return m_user;
}

QString QTdMessageChatDeleteMember::qmlUserId() const
{
    return m_uid.toQmlValue();
}

qint64 QTdMessageChatDeleteMember::userId() const
{
    return m_uid.value();
}

void QTdMessageChatDeleteMember::updateTypeText()
{
    m_typeText = m_senderUserId == userId() ? gettext("left the group") : gettext("removed a member");
}

void QTdMessageChatDeleteMember::setSenderUserId(const qint64 senderUserId)
{
    m_senderUserId = senderUserId;
    updateTypeText();
}

void QTdMessageChatDeleteMember::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    if (json.contains("user_id")) {
        m_uid = json["user_id"].toVariant().toLongLong();
        emit contentChanged();

        updateTypeText();
        auto *user = QTdUsers::instance()->model()->getByUid(m_uid.toQmlValue());
        if (user) {
            m_user = user;
            emit userChanged();
            return;
        }

        QScopedPointer<QTdGetUserRequest> request(new QTdGetUserRequest);
        request->setUserId(m_uid.value());
        m_watcher.setFuture(request->sendAsync());
    }
}

void QTdMessageChatDeleteMember::handleResponse()
{
    const QTdResponse resp = m_watcher.result();
    if (resp.isError()) {
        qWarning() << resp.errorString();
        return;
    }
    m_user = new QTdUser(this);
    m_user->unmarshalJson(resp.json());
    emit userChanged();
}
