#include "qtdnetworktype.h"

QTdNetworkType::QTdNetworkType(QObject *parent)
    : QTdObject(parent)
{
}

QTdNetworkTypeMobile::QTdNetworkTypeMobile(QObject *parent)
    : QTdNetworkType(parent)
{
    setType(NETWORK_TYPE_MOBILE);
}

QTdNetworkTypeMobileRoaming::QTdNetworkTypeMobileRoaming(QObject *parent)
    : QTdNetworkType(parent)
{
    setType(NETWORK_TYPE_MOBILE_ROAMING);
}

QTdNetworkTypeNone::QTdNetworkTypeNone(QObject *parent)
    : QTdNetworkType(parent)
{
    setType(NETWORK_TYPE_NONE);
}

QTdNetworkTypeOther::QTdNetworkTypeOther(QObject *parent)
    : QTdNetworkType(parent)
{
    setType(NETWORK_TYPE_OTHER);
}

QTdNetworkTypeWiFi::QTdNetworkTypeWiFi(QObject *parent)
    : QTdNetworkType(parent)
{
    setType(NETWORK_TYPE_WIFI);
}
