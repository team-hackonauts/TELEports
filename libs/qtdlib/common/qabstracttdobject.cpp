#include "qabstracttdobject.h"

QTdObject::QTdObject(QObject *parent)
    : QObject(parent)
    , m_type(UNKNOWN)
{
}

QTdObject::Type QTdObject::type() const
{
    return m_type;
}

QString QTdObject::typeString() const
{
    return m_typeString;
}

void QTdObject::unmarshalJson(const QJsonObject &json)
{
    m_typeString = json["@type"].toString();
}

QJsonObject QTdObject::marshalJson()
{
    return QJsonObject();
}

void QTdObject::setType(const QTdObject::Type type)
{
    m_type = type;
    emit typeChanged(m_type);
}
