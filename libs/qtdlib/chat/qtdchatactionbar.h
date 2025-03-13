#ifndef QTDCHATACTIONBAR_H
#define QTDCHATACTIONBAR_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdChatActionBar : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionBar)

public:
    explicit QTdChatActionBar(QObject *parent = nullptr);

};

class QTdChatActionBarAddContact : public QTdChatActionBar
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionBarAddContact)

public:
    explicit QTdChatActionBarAddContact(QObject *parent = nullptr);
};

class QTdChatActionBarInviteMembers : public QTdChatActionBar
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionBarInviteMembers)

public:
    explicit QTdChatActionBarInviteMembers(QObject *parent = nullptr);
};

class QTdChatActionBarJoinRequest : public QTdChatActionBar
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(bool isChannel READ isChannel)
    Q_PROPERTY(qint32 requestDate READ requestDate)
    Q_DISABLE_COPY(QTdChatActionBarJoinRequest)

public:
    explicit QTdChatActionBarJoinRequest(QObject *parent = nullptr);

    QString title();
    bool isChannel();
    qint32 requestDate();

    void unmarshalJson(const QJsonObject &json) override;

private:
    QString m_title;
    bool m_isChannel;
    qint32 m_requestDate;
};

class QTdChatActionBarReportAddBlock : public QTdChatActionBar
{
    Q_OBJECT
    Q_PROPERTY(bool canUnarchive READ canUnarchive)
    Q_PROPERTY(qint32 distance READ distance)
    Q_DISABLE_COPY(QTdChatActionBarReportAddBlock)

public:
    explicit QTdChatActionBarReportAddBlock(QObject *parent = nullptr);

    bool canUnarchive();
    qint32 distance();

    void unmarshalJson(const QJsonObject &json) override;

private:
    bool m_canUnarchive;
    qint32 m_distance;
};

class QTdChatActionBarReportSpam : public QTdChatActionBar
{
    Q_OBJECT
    Q_PROPERTY(bool canUnarchive READ canUnarchive)
    Q_DISABLE_COPY(QTdChatActionBarReportSpam)

public:
    explicit QTdChatActionBarReportSpam(QObject *parent = nullptr);

    bool canUnarchive();

    void unmarshalJson(const QJsonObject &json) override;

private:
    bool m_canUnarchive;
};

class QTdChatActionBarReportUnrelatedLocation : public QTdChatActionBar
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionBarReportUnrelatedLocation)

public:
    explicit QTdChatActionBarReportUnrelatedLocation(QObject *parent = nullptr);
};

class QTdChatActionBarSharePhoneNumber : public QTdChatActionBar
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionBarSharePhoneNumber)

public:
    explicit QTdChatActionBarSharePhoneNumber(QObject *parent = nullptr);
};

struct QTdChatActionBarFactory
{
    static QTdChatActionBar *create(const QJsonObject &json, QObject *parent = Q_NULLPTR);
};
#endif // QTDCHATACTIONBAR_H
