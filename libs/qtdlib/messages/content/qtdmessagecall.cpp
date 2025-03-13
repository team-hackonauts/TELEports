#include "qtdmessagecall.h"
#include "utils/i18n.h"
#include <QDebug>
#include <QtMath>

QTdMessageCall::QTdMessageCall(QObject *parent)
    : QTdMessageContent(parent)
    , m_discardReason(Q_NULLPTR)
    , m_duration(0)
    , m_minutes(0)
    , m_seconds(0)
{
    setType(MESSAGE_CALL);
}

QTdCallDiscardReason *QTdMessageCall::discardReason() const
{
    return m_discardReason.data();
}

qint32 QTdMessageCall::duration() const
{
    return m_duration;
}

QString QTdMessageCall::hours() const
{
    return QString("%1").arg(m_hours, 2, 10, QChar('0'));
}

QString QTdMessageCall::minutes() const
{
    return QString("%1").arg(m_minutes, 2, 10, QChar('0'));
}

QString QTdMessageCall::seconds() const
{
    return QString("%1").arg(m_seconds, 2, 10, QChar('0'));
}

QString QTdMessageCall::typeText() const
{
    return m_typeText;
}

void QTdMessageCall::setOutgoing(const bool isOutgoing)
{
    m_isOutgoing = isOutgoing;
    updateTypeText();
}

void QTdMessageCall::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
    m_duration = json["duration"].toInt();
    m_hours = m_duration / 3600;
    m_minutes = m_duration / 60 - m_hours * 60;
    m_seconds = m_duration - m_hours * 3600 - m_minutes * 60;
    const QJsonObject reasonObj = json["discard_reason"].toObject();
    m_reason = reasonObj["@type"].toString();
    updateTypeText();
    emit contentChanged();
}

void QTdMessageCall::updateTypeText()
{
    if (m_reason == QStringLiteral("callDiscardReasonDeclined")) {
        m_typeText = gettext("Call Declined");
        m_discardReason.reset(new QTdCallDiscardReasonDeclined(this));
    } else if (m_reason == QStringLiteral("callDiscardReasonDisconnected")) {
        m_typeText = gettext("Call Disconnected");
        m_discardReason.reset(new QTdCallDiscardReasonDisconnected(this));
    } else if (m_reason == QStringLiteral("callDiscardReasonEmpty")) {
        m_typeText = gettext("Call Ended");
        m_discardReason.reset(new QTdCallDiscardReasonEmpty(this));
    } else if (m_reason == QStringLiteral("callDiscardReasonHungUp")) {
        // TRANSLATORS: This is a duration in hours:minutes:seconds format - only arrange the order, do not translate!
        auto _length = QString(gettext("%1:%2:%3")).arg(hours(), minutes(), seconds());
        m_typeText = m_isOutgoing ? QString(gettext("Outgoing Call (%1)")).arg(_length)
                                  : QString(gettext("Incoming Call (%1)")).arg(_length);
        m_discardReason.reset(new QTdCallDiscardReasonHungUp(this));
    } else if (m_reason == QStringLiteral("callDiscardReasonMissed")) {
        m_typeText = m_isOutgoing ? gettext("Cancelled Call") : gettext("Missed Call");
        m_discardReason.reset(new QTdCallDiscardReasonMissed(this));
    } else {
        m_typeText = gettext("Call");
        m_discardReason.reset();
        qWarning() << "Unknown call discard reason";
    }
}

