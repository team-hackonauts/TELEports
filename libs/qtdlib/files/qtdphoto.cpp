#include "qtdphoto.h"
#include "qtdlocalfile.h"
#include "qtdremotefile.h"

QTdPhoto::QTdPhoto(QObject *parent)
    : QTdObject(parent)
    , m_small(new QTdFile)
    , m_big(new QTdFile)
{
}

QTdFile *QTdPhoto::small() const
{
    return m_small.data();
}

QTdFile *QTdPhoto::big() const
{
    return m_big.data();
}

QString QTdPhoto::smallPhotoPath() {
    if (m_small && !m_small->local()->path().isEmpty()) {
        return "image://photo/" + m_small->local()->path();
    }
    return "";
}

void QTdPhoto::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    if (!json.isEmpty()) {
        m_small->unmarshalJson(json["small"].toObject());
        emit smallChanged(m_small.data());
        m_big->unmarshalJson(json["big"].toObject());
        emit bigChanged(m_big.data());
    }

}
