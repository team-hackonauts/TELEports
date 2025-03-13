#include "qtdinputmessagecontentfactory.h"

#include "content/qtdinputmessageaudio.h"
#include "content/qtdinputmessagecontact.h"
#include "content/qtdinputmessagedocument.h"
#include "content/qtdinputmessagelocation.h"
#include "content/qtdinputmessagephoto.h"
#include "content/qtdinputmessagesticker.h"
#include "content/qtdinputmessagevideo.h"
#include <stdexcept>

QTdInputMessageContentAttachmentCaption *QTdInputMessageContentFactory::create(const InputMessageType type, QObject *parent)
{
    switch (type) {
    case Photo:
        return new QTdInputMessagePhoto(parent);
    case Video:
        return new QTdInputMessageVideo(parent);
    case Audio:
        return new QTdInputMessageAudio(parent);
    case Document:
        return new QTdInputMessageDocument(parent);
    default:
        throw std::invalid_argument( "invalid input message type" );
    }
}
