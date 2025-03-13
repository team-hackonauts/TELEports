#ifndef QTDINPUTMESSAGECONTENTATTACHMENTCAPTION_H
#define QTDINPUTMESSAGECONTENTATTACHMENTCAPTION_H

#include <QObject>
#include <QJsonArray>
#include "qtdinputmessagecontent.h"
#include "content/imessageattachmentcontent.h"
#include "content/imessagecaptioncontent.h"

class QTdInputMessageContentAttachmentCaption : public QTdInputMessageContent, public IMessageCaptionContent, public IMessageAttachmentContent
{
    Q_OBJECT
    Q_INTERFACES(IMessageCaptionContent IMessageAttachmentContent)
public:
    explicit QTdInputMessageContentAttachmentCaption(QObject *parent = nullptr);
    virtual QJsonObject marshalJson() = 0;
    virtual void setAttachmentPath(const QString &url) = 0;
    virtual void setCaption(const QString &text) = 0;
    virtual void setCaptionEntities(const QJsonArray &entities) = 0;
};
#endif // QTDINPUTMESSAGECONTENTATTACHMENTCAPTION_H
