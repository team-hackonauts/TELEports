#ifndef IMESSAGECAPTIONCONTENT_H
#define IMESSAGECAPTIONCONTENT_H

#include <QtPlugin>
#include <QString>
#include <QJsonArray>

class IMessageCaptionContent
{

public:
    virtual void setCaption(const QString &text) = 0;
    virtual void setCaptionEntities(const QJsonArray &entities) = 0;
};

Q_DECLARE_INTERFACE(IMessageCaptionContent, "IMessageCaptionContent/1.0")

#endif // IMESSAGECAPTIONCONTENT_H