#include "qtdmessageschedulingstate.h"

QTdMessageSchedulingState::QTdMessageSchedulingState(QObject *parent)
    : QTdObject(parent)
{
}

QTdMessageSchedulingStateSendAtDate::QTdMessageSchedulingStateSendAtDate(QObject *parent)
    : QTdMessageSchedulingState(parent)
{
    setType(MESSAGE_SCHEDULING_STATE_AT_DATE);
}

QTdMessageSchedulingStateSendWhenOnline::QTdMessageSchedulingStateSendWhenOnline(QObject *parent)
    : QTdMessageSchedulingState(parent)
{
    setType(MESSAGE_SCHEDULING_STATE_WHEN_ONLINE);
}
