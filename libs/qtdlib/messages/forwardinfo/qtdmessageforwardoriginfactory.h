#ifndef QTDMESSAGEFORWARDORIGINFACTORY_H
#define QTDMESSAGEFORWARDORIGINFACTORY_H
#include "qtdmessageforwardorigin.h"

struct QTdMessageForwardOriginFactory
{
    static QTdMessageForwardOrigin *create(const QJsonObject &json, QObject *parent);
};

#endif // QTDMESSAGEFORWARDORIGINFACTORY_H
