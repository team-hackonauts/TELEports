#include "qtdmessageinteractioninfo.h"

QTdMessageInteractionInfo::QTdMessageInteractionInfo(QObject *parent)
    : QTdObject(parent)
    , m_viewCount(0)
    , m_forwardCount(0)
{
    setType(MESSAGE_INTERACTION_INFO);
}

qint32 QTdMessageInteractionInfo::viewCount() const
{
    return m_viewCount.value();
}

QString QTdMessageInteractionInfo::qmlViewCount() const
{
    return m_viewCount.toQmlValue();
}

qint32 QTdMessageInteractionInfo::forwardCount() const
{
    return m_forwardCount.value();
}

QString QTdMessageInteractionInfo::qmlForwardCount() const
{
    return m_forwardCount.toQmlValue();
}

void QTdMessageInteractionInfo::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_viewCount = json["view_count"].toInt();
    m_forwardCount = json["forward_count"].toInt();
    emit interactionInfoChanged();
}
