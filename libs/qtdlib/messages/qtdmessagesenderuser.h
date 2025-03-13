#ifndef QTDMESSAGESENDERUSER_H
#define QTDMESSAGESENDERUSER_H

#include "qtdmessagesender.h"
#include "user/qtduser.h"

/**
 * @brief The QTdMessageSenderUser class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_sender_user.html
 */
class QTdMessageSenderUser : public QTdMessageSender
{
    Q_OBJECT
    Q_PROPERTY(QTdUser *user READ user NOTIFY userChanged)
    Q_PROPERTY(QString smallPhotoPath READ smallPhotoPath NOTIFY userChanged)
public:
    explicit QTdMessageSenderUser(QObject *parent = nullptr);

    QTdUser *user() const;
    QString displayName() const;
    QString fullName() const;
    QTdPhoto *photo() const;
    QString smallPhotoPath() const;
    QString initials() const;

    void unmarshalJson(const QJsonObject &json, const QString &id_key) override;
signals:
    void userChanged();

private:
    Q_DISABLE_COPY(QTdMessageSenderUser)
    QTdUser *m_user;
    bool m_waitingForUser;

    void updateUser(const qint64 &userId);
};

#endif // QTDMESSAGESENDERUSER_H
