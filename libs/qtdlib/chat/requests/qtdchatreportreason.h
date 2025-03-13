#ifndef QTDCHATREPORTREASON_H
#define QTDCHATREPORTREASON_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdChatReportReason : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatReportReason)

public:
    explicit QTdChatReportReason(QObject *parent = nullptr);

    enum ChatReportReasonType {
        ChatReportReasonChildAbuse,
        ChatReportReasonCopyright,
        ChatReportReasonCustom,
        ChatReportReasonFake,
        ChatReportReasonPornography,
        ChatReportReasonSpam,
        ChatReportReasonUnrelatedLocation,
        ChatReportReasonViolence
    };
    Q_ENUM(ChatReportReasonType)

    QJsonObject marshalJson();

protected:
    QString m_type;
    
};

class QTdChatReportReasonChildAbuse : public QTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatReportReasonChildAbuse)

public:
    explicit QTdChatReportReasonChildAbuse(QObject *parent = nullptr);
};

class QTdChatReportReasonCopyright : public QTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatReportReasonCopyright)

public:
    explicit QTdChatReportReasonCopyright(QObject *parent = nullptr);
};

class QTdChatReportReasonCustom : public QTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatReportReasonCustom)

public:
    explicit QTdChatReportReasonCustom(QObject *parent = nullptr);
};

class QTdChatReportReasonFake : public QTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatReportReasonFake)

public:
    explicit QTdChatReportReasonFake(QObject *parent = nullptr);
};

class QTdChatReportReasonPornograhpy : public QTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatReportReasonPornograhpy)

public:
    explicit QTdChatReportReasonPornograhpy(QObject *parent = nullptr);
};

class QTdChatReportReasonSpam : public QTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatReportReasonSpam)

public:
    explicit QTdChatReportReasonSpam(QObject *parent = nullptr);
};

class QTdChatReportReasonUnrelatedLocation : public QTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatReportReasonUnrelatedLocation)

public:
    explicit QTdChatReportReasonUnrelatedLocation(QObject *parent = nullptr);
};

class QTdChatReportReasonViolence : public QTdChatReportReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatReportReasonViolence)

public:
    explicit QTdChatReportReasonViolence(QObject *parent = nullptr);
};

#endif // QTDCHATREPORTREASON_H