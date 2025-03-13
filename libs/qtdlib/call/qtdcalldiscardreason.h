#ifndef QTDCALLDISCARDREASON_H
#define QTDCALLDISCARDREASON_H

#include <QObject>
#include "common/qabstracttdobject.h"

/**
 * @brief The QTdCallDiscardReason class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_call_discard_reason.html
 */
class QTdCallDiscardReason : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdCallDiscardReason)
public:
    explicit QTdCallDiscardReason(QObject *parent = nullptr);
};

/**
 * @brief The QTdCallDiscardReasonDeclined class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_declined.html
 */
class QTdCallDiscardReasonDeclined : public QTdCallDiscardReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdCallDiscardReasonDeclined)
public:
    explicit QTdCallDiscardReasonDeclined(QObject *parent = nullptr);
    QJsonObject marshalJson();
};

/**
 * @brief The QTdCallDiscardReasonDisconnected class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_disconnected.html
 */
class QTdCallDiscardReasonDisconnected : public QTdCallDiscardReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdCallDiscardReasonDisconnected)
public:
    explicit QTdCallDiscardReasonDisconnected(QObject *parent = nullptr);
    QJsonObject marshalJson();
};

/**
 * @brief The QTdCallDiscardReasonEmpty class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_empty.html
 */
class QTdCallDiscardReasonEmpty : public QTdCallDiscardReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdCallDiscardReasonEmpty)
public:
    explicit QTdCallDiscardReasonEmpty(QObject *parent = nullptr);
    QJsonObject marshalJson();
};

/**
 * @brief The QTdCallDiscardReasonHungUp class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_hung_up.html
 */
class QTdCallDiscardReasonHungUp : public QTdCallDiscardReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdCallDiscardReasonHungUp)
public:
    explicit QTdCallDiscardReasonHungUp(QObject *parent = nullptr);
    QJsonObject marshalJson();
};

/**
 * @brief The QTdCallDiscardReasonMissed class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1call_discard_reason_missed.html
 */
class QTdCallDiscardReasonMissed : public QTdCallDiscardReason
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdCallDiscardReasonMissed)
public:
    explicit QTdCallDiscardReasonMissed(QObject *parent = nullptr);
    QJsonObject marshalJson();
};
#endif // QTDCALLDISCARDREASON_H
