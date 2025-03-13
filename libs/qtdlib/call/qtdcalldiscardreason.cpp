#include "qtdcalldiscardreason.h"

QTdCallDiscardReason::QTdCallDiscardReason(QObject *parent)
    : QTdObject(parent)
{
    setType(CALL_DISCARD_REASON);
}

QTdCallDiscardReasonDeclined::QTdCallDiscardReasonDeclined(QObject *parent)
{
    setType(CALL_DISCARD_REASON_DECLINED);
}

QJsonObject QTdCallDiscardReasonDeclined::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonDeclined" },
    };
}

QTdCallDiscardReasonDisconnected::QTdCallDiscardReasonDisconnected(QObject *parent)
{
    setType(CALL_DISCARD_REASON_DISCONNECTED);
}

QJsonObject QTdCallDiscardReasonDisconnected::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonDisconnected" },
    };
}

QTdCallDiscardReasonEmpty::QTdCallDiscardReasonEmpty(QObject *parent)
{
    setType(CALL_DISCARD_REASON_EMPTY);
}

QJsonObject QTdCallDiscardReasonEmpty::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonEmpty" },
    };
}

QTdCallDiscardReasonHungUp::QTdCallDiscardReasonHungUp(QObject *parent)
{
    setType(CALL_DISCARD_REASON_HUNG_UP);
}

QJsonObject QTdCallDiscardReasonHungUp::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonHungUp" },
    };
}

QTdCallDiscardReasonMissed::QTdCallDiscardReasonMissed(QObject *parent)
{
    setType(CALL_DISCARD_REASON_MISSED);
}

QJsonObject QTdCallDiscardReasonMissed::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonMissed" },
    };
}
