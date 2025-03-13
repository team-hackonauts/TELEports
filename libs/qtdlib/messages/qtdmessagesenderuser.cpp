#include "qtdmessagesenderuser.h"
#include "client/qtdclient.h"
#include "user/qtdusers.h"
#include "utils/debug.h"

QTdMessageSenderUser::QTdMessageSenderUser(QObject *parent)
    : QTdMessageSender(parent)
    , m_user(nullptr)
    , m_waitingForUser(false)
{
    setType(MESSAGE_SENDER_USER);
}

QTdUser *QTdMessageSenderUser::user() const
{
    return m_user;
}

void QTdMessageSenderUser::unmarshalJson(const QJsonObject &json, const QString &id_key)
{
    QTdMessageSender::unmarshalJson(json, "user_id");
    updateUser(id());
}

void QTdMessageSenderUser::updateUser(const qint64 &userId)
{
    if (userId != id()) {
        return;
    }
    if (m_user) {
        m_user = nullptr;
    }

    auto *users = QTdUsers::instance()->model();
    m_user = users->getByUid(QString::number(userId));
    if (m_user) {
        emit userChanged();
        emit dataChanged();
        if (m_waitingForUser) {
            disconnect(QTdUsers::instance(), &QTdUsers::userCreated, this, &QTdMessageSenderUser::updateUser);
            m_waitingForUser = false;
        }
        return;
    }
    connect(QTdUsers::instance(), &QTdUsers::userCreated, this, &QTdMessageSenderUser::updateUser);
    QTdClient::instance()->send(QJsonObject {
            { "@type", "getUser" },
            { "user_id", userId } });
    m_waitingForUser = true;
}

QString QTdMessageSenderUser::displayName() const
{
    if (!m_user) {
        return QString();
    }

    QString name = m_user->firstName();

    if (name.isEmpty()) {
        name = m_user->username();
    }

    return name;
}

QString QTdMessageSenderUser::fullName() const
{
    if (!m_user) {
        return QString();
    }

    return m_user->fullName();
}

QTdPhoto *QTdMessageSenderUser::photo() const
{
    if (!m_user) {
        return nullptr;
    }

    return m_user->profilePhoto();
}

QString QTdMessageSenderUser::initials() const
{
    if (!m_user) {
        return QString();
    }

    return m_user->initials();
}

QString QTdMessageSenderUser::smallPhotoPath() const {
    return m_user->smallPhotoPath();
}
