#ifndef QTDMESSAGESCREENSHOTTAKEN_H
#define QTDMESSAGESCREENSHOTTAKEN_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessageScreenshotTaken : public QTdMessageContent
{
    Q_OBJECT
public:
    explicit QTdMessageScreenshotTaken(QObject *parent = nullptr);

    void unmarshalJson(const QJsonObject &json) override;

private:
    Q_DISABLE_COPY(QTdMessageScreenshotTaken)
};

#endif // QTDMESSAGESCREENSHOTTAKEN_H
