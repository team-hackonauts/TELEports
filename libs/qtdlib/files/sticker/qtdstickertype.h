#ifndef QTDSTICKERTYPE_H
#define QTDSTICKERTYPE_H

#include <QObject>
#include <QPointer>
#include "common/qabstracttdobject.h"

class QTdStickerType : public QTdObject
{
    Q_OBJECT

public:
    explicit QTdStickerType(QObject *parent = nullptr);

    virtual void unmarshalJson(const QJsonObject &json) { };

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdStickerType)
};

class QTdStickerTypeRegular : public QTdStickerType
{
    Q_OBJECT

public:
    explicit QTdStickerTypeRegular(QObject *parent = nullptr);

};

class QTdStickerTypeMask : public QTdStickerType
{
    Q_OBJECT

public:
    explicit QTdStickerTypeMask(QObject *parent = nullptr);

};

class QTdStickerTypeCustomEmoji : public QTdStickerType
{
    Q_OBJECT

public:
    explicit QTdStickerTypeCustomEmoji(QObject *parent = nullptr);

};

struct QTdStickerTypeFactory
{
    static QTdStickerType *create(const QJsonObject &json, QObject *parent = Q_NULLPTR);
};

#endif // QTDSTICKERTYPE_H
