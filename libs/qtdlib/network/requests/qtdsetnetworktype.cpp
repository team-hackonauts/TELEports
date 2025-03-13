#include "qtdsetnetworktype.h"

QTdSetNetworkTypeRequest::QTdSetNetworkTypeRequest(QObject *parent)
    : QTdOkRequest(parent)
    , m_networkType(Q_NULLPTR)
{
}

void QTdSetNetworkTypeRequest::setNetworkType(QTdNetworkType *networkType)
{
    m_networkType = networkType;
}

QJsonObject QTdSetNetworkTypeRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "setNetworkType" },
        { "type", m_networkType->marshalJson() },
    };
}
