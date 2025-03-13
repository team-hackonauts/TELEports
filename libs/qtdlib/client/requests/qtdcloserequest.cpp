#include "qtdcloserequest.h"

QTdCloseRequest::QTdCloseRequest(QObject *parent)
    : QTdOkRequest(parent)
{
}

QJsonObject QTdCloseRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "close" }
    };
}
