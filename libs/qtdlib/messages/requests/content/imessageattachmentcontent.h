#ifndef IMESSAGEATTACHMENTCONTENT_H
#define IMESSAGEATTACHMENTCONTENT_H

#include <QtPlugin>
#include <QString>

class IMessageAttachmentContent
{

public:
    virtual void setAttachmentPath(const QString &url) = 0;
};

Q_DECLARE_INTERFACE(IMessageAttachmentContent, "IMessageAttachmentContent/1.0")

#endif // IMESSAGEATTACHMENTCONTENT_H