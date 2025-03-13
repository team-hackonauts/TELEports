#include "qabstractint64id.h"
#include <QDebug>

QAbstractInt64Id::QAbstractInt64Id(QObject *parent)
    : QTdObject(parent)
    , m_id(0)
{
}

qint64 QAbstractInt64Id::id() const
{
    return m_id.value();
}

QString QAbstractInt64Id::qmlId() const
{
    return m_id.toQmlValue();
}

QJsonValue QAbstractInt64Id::jsonId() const
{
    return m_id.toJsonValue();
}

void QAbstractInt64Id::unmarshalJson(const QJsonObject &json, const QString &id_key)
{
    QTdObject::unmarshalJson(json);
    auto new_id = json[id_key].toVariant().toLongLong();
    if (m_id.value() != new_id) {
        m_id = new_id;
        emit idChanged(m_id.value());
    }
}

QAbstractInt64Id *QAbstractInt64Id::create(const QJsonObject &json, QObject *parent)
{
    auto *obj = new QAbstractInt64Id(parent);
    obj->unmarshalJson(json);
    return obj;
}
