#include "qtdminithumbnail.h"

QTdMiniThumbnail::QTdMiniThumbnail(QObject *parent)
    : QTdObject(parent)
    , m_data("")
    , m_width(0)
    , m_height(0)
{
    setType(MINITHUMBNAIL);
}

QString QTdMiniThumbnail::data() const
{
    return m_data;
}

QString QTdMiniThumbnail::dataURL() const
{
    return QString("data:image/jpeg;base64,%1").arg(m_data);
}

qint32 QTdMiniThumbnail::width() const
{
    return m_width;
}

qint32 QTdMiniThumbnail::height() const
{
    return m_height;
}

void QTdMiniThumbnail::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_data = json["data"].toString();
    m_width = qint32(json["width"].toInt());
    m_height = qint32(json["height"].toInt());
    emit miniThumbnailChanged();
}
