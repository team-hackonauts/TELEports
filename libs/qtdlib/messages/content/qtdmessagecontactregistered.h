#ifndef QTDMESSAGECONTACTREGISTERED_H
#define QTDMESSAGECONTACTREGISTERED_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessageContactRegistered : public QTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageContactRegistered)
public:
    explicit QTdMessageContactRegistered(QObject *parent = nullptr);

};

#endif // QTDMESSAGECONTACTREGISTERED_H
