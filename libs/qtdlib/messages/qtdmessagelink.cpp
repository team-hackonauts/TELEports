#include "qtdmessagelink.h"

QTdMessageLink::QTdMessageLink(QObject *parent)
    : QTdObject(parent)
{
    setType(MESSAGE_LINK);
}

QString QTdMessageLink::link() const {
    return m_link;
}

bool QTdMessageLink::isPublic() const {
    return m_is_public;
}


void QTdMessageLink::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_link = json["link"].toString();
    m_is_public = json["is_public"].toBool();
    emit messageLinkChanged();
}