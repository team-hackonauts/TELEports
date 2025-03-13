#ifndef QTDSTICKERFORMAT_H
#define QTDSTICKERFORMAT_H

#include <QObject>
#include <QPointer>
#include "common/qabstracttdobject.h"

class QTdStickerFormat : public QTdObject
{
    Q_OBJECT

public:
    explicit QTdStickerFormat(QObject *parent = nullptr);

    virtual void unmarshalJson(const QJsonObject &json) { };

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdStickerFormat)
};

class QTdStickerFormatWebp : public QTdStickerFormat
{
    Q_OBJECT

public:
    explicit QTdStickerFormatWebp(QObject *parent = nullptr);

};

class QTdStickerFormatTgs : public QTdStickerFormat
{
    Q_OBJECT

public:
    explicit QTdStickerFormatTgs(QObject *parent = nullptr);

};

class QTdStickerFormatWebm : public QTdStickerFormat
{
    Q_OBJECT

public:
    explicit QTdStickerFormatWebm(QObject *parent = nullptr);

};

struct QTdStickerFormatFactory
{
    static QTdStickerFormat *create(const QJsonObject &json, QObject *parent = Q_NULLPTR);
};

#endif // QTDSTICKERFORMAT_H
