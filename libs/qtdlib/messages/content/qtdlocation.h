#ifndef QTDLOCATION_H
#define QTDLOCATION_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdLocation : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(double latitude READ latitude NOTIFY entityChanged)
    Q_PROPERTY(double longitude READ longitude NOTIFY entityChanged)
public:
    explicit QTdLocation(QObject *parent = nullptr);

    double latitude() const;
    void setLatitude(const double value);

    double longitude() const;
    void setLongitude(const double value);

    void unmarshalJson(const QJsonObject &json) override;
    QJsonObject marshalJson();

signals:
    void entityChanged();

private:
    Q_DISABLE_COPY(QTdLocation)
    double m_latitude;
    double m_longitude;
};

#endif // QTDLOCATION_H
