#include "qtdlocation.h"

QTdLocation::QTdLocation(QObject *parent)
    : QTdObject(parent)
    , m_latitude(0)
    , m_longitude(0)
{
    setType(TEXT_ENTITY);
}

double QTdLocation::latitude() const
{
    return m_latitude;
}

void QTdLocation::setLatitude(const double value)
{
    m_latitude = value;
}

double QTdLocation::longitude() const
{
    return m_longitude;
}

void QTdLocation::setLongitude(const double value)
{
    m_longitude = value;
}

void QTdLocation::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_latitude = double(json["latitude"].toDouble());
    m_longitude = double(json["longitude"].toDouble());
    emit entityChanged();
}

QJsonObject QTdLocation::marshalJson()
{
    return QJsonObject{
        { "latitude", m_latitude },
        { "longitude", m_longitude }
    };
}
