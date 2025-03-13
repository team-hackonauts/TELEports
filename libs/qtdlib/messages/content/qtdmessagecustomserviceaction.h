#ifndef QTDMESSAGECUSTOMSERVICEACTION_H
#define QTDMESSAGECUSTOMSERVICEACTION_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessageCustomServiceAction : public QTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageCustomServiceAction)
    Q_PROPERTY(QString text READ text NOTIFY contentChanged)
public:
    explicit QTdMessageCustomServiceAction(QObject *parent = nullptr);

    QString text() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    QString m_text;
};

#endif // QTDMESSAGECUSTOMSERVICEACTION_H
