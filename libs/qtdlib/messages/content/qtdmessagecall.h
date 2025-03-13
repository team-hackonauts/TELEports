#ifndef QTDMESSAGECALL_H
#define QTDMESSAGECALL_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "call/qtdcalldiscardreason.h"

/**
 * @brief The QTdMessageCall class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_call.html
 */
class QTdMessageCall : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdCallDiscardReason *discardReason READ discardReason NOTIFY contentChanged)
    Q_PROPERTY(qint32 duration READ duration NOTIFY contentChanged)
    Q_PROPERTY(QString hours READ hours NOTIFY contentChanged)
    Q_PROPERTY(QString minutes READ minutes NOTIFY contentChanged)
    Q_PROPERTY(QString seconds READ seconds NOTIFY contentChanged)
    Q_PROPERTY(QString typeText READ typeText NOTIFY contentChanged)
public:
    explicit QTdMessageCall(QObject *parent = nullptr);

    QTdCallDiscardReason *discardReason() const;

    qint32 duration() const;
    QString hours() const;
    QString minutes() const;
    QString seconds() const;
    QString typeText() const;

    void setOutgoing(const bool isOutgoing);
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    void updateTypeText();
    QScopedPointer<QTdCallDiscardReason> m_discardReason;
    qint32 m_duration;
    qint32 m_hours;
    qint32 m_minutes;
    qint32 m_seconds;
    QString m_reason;
    bool m_isOutgoing;
};

#endif // QTDMESSAGECALL_H
