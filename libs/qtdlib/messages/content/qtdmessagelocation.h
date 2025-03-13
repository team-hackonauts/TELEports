#ifndef QTDMESSAGELOCATION_H
#define QTDMESSAGELOCATION_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "qtdlocation.h"
#include "qtdformattedtext.h"

class QTdMessageLocation : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdLocation *location READ location NOTIFY dataChanged)
public:
    explicit QTdMessageLocation(QObject *parent = nullptr);

    QTdLocation *location() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessageLocation)
    QScopedPointer<QTdLocation> m_location;
};

#endif // QTDMESSAGELOCATION_H
