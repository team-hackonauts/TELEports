#include "qtdinputmessagecontent.h"
#include <libintl.h>

QTdInputMessageContent::QTdInputMessageContent(QObject *parent)
    : QTdObject(parent)
{
    setType(INPUT_MESSAGE);
}
