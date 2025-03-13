#ifndef QTDSTICKERSETS_H
#define QTDSTICKERSETS_H

#include <QObject>
#include <QPointer>
#include "common/qabstracttdobject.h"
#include "models/QmlObjectListModel.h"
#include "qtdstickerset.h"

class QTdStickerSets : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *stickerSets READ qmlModel)

public:
    explicit QTdStickerSets(QObject *parent = nullptr);

    QObject *qmlModel() const;

    Q_INVOKABLE void loadStickerSets();

    void handleStickerSets(const QJsonObject &json);

signals:

private:
    QPointer<QQmlObjectListModel<QTdStickerSet>> m_stickerSets;
};

#endif // QTDSTICKERSETS_H
