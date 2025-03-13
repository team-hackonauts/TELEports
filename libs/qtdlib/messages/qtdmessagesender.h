#ifndef QTDMESSAGESENDER_H
#define QTDMESSAGESENDER_H

#include <QObject>
#include "common/qabstracttdobject.h"
#include "common/qtdint.h"
#include "files/qtdphoto.h"

/**
 * @brief The QTdMessageSender class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_message_sender.html
 */
class QTdMessageSender : public QAbstractInt64Id
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageSender)
    Q_PROPERTY(QString fullName READ fullName NOTIFY dataChanged)
    Q_PROPERTY(QString displayName READ displayName NOTIFY dataChanged)
    Q_PROPERTY(QTdPhoto *photo READ photo NOTIFY dataChanged)
    Q_PROPERTY(QString avatarColor READ avatarColor NOTIFY dataChanged)
    Q_PROPERTY(QString initials READ initials NOTIFY dataChanged)
public:
    explicit QTdMessageSender(QObject *parent = nullptr);

    virtual QString displayName() const = 0;
    virtual QString fullName() const = 0;
    virtual QTdPhoto *photo() const = 0;
    virtual QString avatarColor() const;
    virtual QString initials() const = 0;

signals:
    void dataChanged();
};

/**
 * @brief The QTdMessageSenderUnimplemented class
 *
 * Stops the app from crashing if Telegram adds an unsupported sender type
 */
class QTdMessageSenderUnimplemented : public QTdMessageSender
{
    Q_OBJECT
public:
    explicit QTdMessageSenderUnimplemented(QObject *parent = nullptr);

    QString displayName() const;
    QString fullName() const;
    QTdPhoto *photo() const;
    QString initials() const;

private:
    Q_DISABLE_COPY(QTdMessageSenderUnimplemented)
};

struct QTdMessageSenderFactory
{
    static QTdMessageSender *create(const QJsonObject &json, QObject *parent = nullptr);
};

#endif // QTDMESSAGESENDER_H
