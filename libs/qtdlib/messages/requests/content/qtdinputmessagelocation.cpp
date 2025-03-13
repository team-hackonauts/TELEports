#include "qtdinputmessagelocation.h"

QTdInputMessageLocation::QTdInputMessageLocation(QObject *parent)
    : QTdInputMessageContent(parent)
    , m_location(Q_NULLPTR)
    , m_live_period(0)
{
}

void QTdInputMessageLocation::setLocation(double latitude, double longitude)
{
    m_location.reset(new QTdLocation());
    m_location->setLatitude(latitude);
    m_location->setLongitude(longitude);
}

void QTdInputMessageLocation::setLivePeriod(const qint32 live_period)
{
    m_live_period = live_period;
}
QJsonObject QTdInputMessageLocation::marshalJson()
{
    return QJsonObject{
        { "@type", "inputMessageLocation" },
        { "location", m_location->marshalJson() },
        { "live_period", m_live_period }
    };
}
