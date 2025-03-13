#ifndef QTDINPUTMESSAGECONTENTFACTORY_H
#define QTDINPUTMESSAGECONTENTFACTORY_H

#include "qtdinputmessagecontentattachmentcaption.h"

enum InputMessageType {
    Photo,
    Video,
    Audio,
    Document,
};

struct QTdInputMessageContentFactory
{
    static QTdInputMessageContentAttachmentCaption *create(const InputMessageType type, QObject *parent = nullptr);
};

#endif // QTDINPUTMESSAGECONTENTFACTORY_H
