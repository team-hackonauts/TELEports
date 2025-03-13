#include "qtdinputmessagesticker.h"

QTdInputMessageSticker::QTdInputMessageSticker(QObject *parent)
    : QTdInputMessageContent(parent)
    , m_sticker(nullptr)
{
}

void QTdInputMessageSticker::setSticker(QTdSticker *sticker)
{
    m_sticker = sticker;
}

QJsonObject QTdInputMessageSticker::marshalJson()
{
    if (!m_sticker) {
        qDebug() << "Tried to marshal QTdInputMessageSticker with invalid sticker pointer";
        return QJsonObject();
    }
    return QJsonObject{
        { "@type", "inputMessageSticker" },
        { "sticker", QJsonObject{ { "@type", "inputFileRemote" }, { "id", m_sticker->sticker()->remote()->id() } } },
    };
}
