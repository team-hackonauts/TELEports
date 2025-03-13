#include "qtdmessagescreenshottaken.h"

QTdMessageScreenshotTaken::QTdMessageScreenshotTaken(QObject *parent)
    : QTdMessageContent(parent)
{
    setType(MESSAGE_SCREENSHOT_TAKEN);
}

void QTdMessageScreenshotTaken::unmarshalJson(const QJsonObject &json)
{
    QTdMessageContent::unmarshalJson(json);
}
