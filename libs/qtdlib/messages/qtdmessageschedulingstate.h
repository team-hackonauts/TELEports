#ifndef QTDMESSAGESCHEDULINGSTATE_H
#define QTDMESSAGESCHEDULINGSTATE_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdMessageSchedulingState : public QTdObject
{
    Q_OBJECT
public:
    explicit QTdMessageSchedulingState(QObject *parent = nullptr);
};

class QTdMessageSchedulingStateSendAtDate : public QTdMessageSchedulingState
{
    Q_OBJECT
public:
    explicit QTdMessageSchedulingStateSendAtDate(QObject *parent = nullptr);
};

class QTdMessageSchedulingStateSendWhenOnline : public QTdMessageSchedulingState
{
    Q_OBJECT
public:
    explicit QTdMessageSchedulingStateSendWhenOnline(QObject *parent = nullptr);
};
#endif // QTDMESSAGESCHEDULINGSTATE_H
