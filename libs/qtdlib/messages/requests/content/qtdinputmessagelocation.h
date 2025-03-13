#ifndef QTDINPUTMESSAGELOCATION_H
#define QTDINPUTMESSAGELOCATION_H

#include <QObject>
#include <QPointer>
#include <QJsonArray>
#include <QString>

#include "../qtdinputmessagecontent.h"
#include "../../content/qtdlocation.h"

class QTdInputMessageLocation : public QTdInputMessageContent
{
    Q_OBJECT
public:
    explicit QTdInputMessageLocation(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setLocation(const double latitude, const double longitude);
    void setLivePeriod(const qint32 live_period);

private:
    QScopedPointer<QTdLocation> m_location;
    qint32 m_live_period;
    Q_DISABLE_COPY(QTdInputMessageLocation)
};

#endif // QTDINPUTMESSAGELOCATION_H
