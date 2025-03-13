#ifndef QTDNETWORKTYPE_H
#define QTDNETWORKTYPE_H

#include "common/qabstracttdobject.h"
#include <QObject>

class QTdNetworkType : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdNetworkType)
public:
    explicit QTdNetworkType(QObject *parent = nullptr);
};

class QTdNetworkTypeMobile : public QTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdNetworkTypeMobile)
public:
    explicit QTdNetworkTypeMobile(QObject *parent = Q_NULLPTR);
};

class QTdNetworkTypeMobileRoaming : public QTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdNetworkTypeMobileRoaming)
public:
    explicit QTdNetworkTypeMobileRoaming(QObject *parent = Q_NULLPTR);
};

class QTdNetworkTypeNone : public QTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdNetworkTypeNone)
public:
    explicit QTdNetworkTypeNone(QObject *parent = Q_NULLPTR);
};

class QTdNetworkTypeOther : public QTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdNetworkTypeOther)
public:
    explicit QTdNetworkTypeOther(QObject *parent = Q_NULLPTR);
};

class QTdNetworkTypeWiFi : public QTdNetworkType
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdNetworkTypeWiFi)
public:
    explicit QTdNetworkTypeWiFi(QObject *parent = Q_NULLPTR);
};

#endif // QTDNETWORKTYPE_H