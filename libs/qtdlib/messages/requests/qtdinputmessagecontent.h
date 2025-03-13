#ifndef QTDINPUTMESSAGECONTENT_H
#define QTDINPUTMESSAGECONTENT_H

#include <QObject>
#include <QJsonArray>
#include "common/qabstracttdobject.h"

class QTdInputMessageContent : public QTdObject
{
    Q_OBJECT
    // Q_DISABLE_COPY(QTdInputMessageContent)
public:
    explicit QTdInputMessageContent(QObject *parent = nullptr);
    virtual QJsonObject marshalJson() = 0;
};
#endif // QTDINPUTMESSAGECONTENT_H
