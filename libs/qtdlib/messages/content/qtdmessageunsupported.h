#ifndef QTDMESSAGEUNSUPPORTED_H
#define QTDMESSAGEUNSUPPORTED_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessageUnsupported : public QTdMessageContent
{
    Q_OBJECT
public:
    explicit QTdMessageUnsupported(QObject *parent = nullptr);

    void unmarshalJson(const QJsonObject &json) override;

private:
    Q_DISABLE_COPY(QTdMessageUnsupported)
};

#endif // QTDMESSAGEUNSUPPORTED_H
