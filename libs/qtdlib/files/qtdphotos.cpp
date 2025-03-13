#include "qtdphotos.h"
#include <QJsonArray>
#include <QDebug>

QTdPhotos::QTdPhotos(QObject *parent)
    : QAbstractInt64Id(parent)
    , m_hasStickers(false)
    , m_sizes(Q_NULLPTR)
{
    m_sizes = new QQmlObjectListModel<QTdPhotoSize>(this, "", "type");
}

QTdPhotos::~QTdPhotos()
{
    m_sizes->clear();
}

void QTdPhotos::unmarshalJson(const QJsonObject &json)
{
    QAbstractInt64Id::unmarshalJson(json);
    m_hasStickers = json["has_stickers"].toBool();
    const QJsonArray sizes = json["sizes"].toArray();
    for (const QJsonValue &size : sizes) {
        auto *s = new QTdPhotoSize();
        s->unmarshalJson(size.toObject());
        m_sizes->append(s);
    }
    emit photosChanged();
}

bool QTdPhotos::hasStickers() const
{
    return m_hasStickers;
}

QObject *QTdPhotos::qmlSizes() const
{
    return m_sizes;
}

QQmlObjectListModel<QTdPhotoSize> *QTdPhotos::sizes() const
{
    return m_sizes;
}
