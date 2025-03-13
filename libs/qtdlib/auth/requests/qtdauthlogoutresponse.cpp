#include "qtdauthlogoutresponse.h"

QTdAuthLogOutResponse::QTdAuthLogOutResponse(QObject *parent)
    : QTdOkRequest(parent)
{
}

QJsonObject QTdAuthLogOutResponse::marshalJson()
{
    return QJsonObject{
        { "@type", "logOut" },
    };
}
