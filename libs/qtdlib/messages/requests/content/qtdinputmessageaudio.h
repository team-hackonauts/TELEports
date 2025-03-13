#ifndef QTDINPUTMESSAGEAUDIO_H
#define QTDINPUTMESSAGEAUDIO_H

#include <QObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>

#include "../qtdinputmessagecontentattachmentcaption.h"

class QTdInputMessageAudio : public QTdInputMessageContentAttachmentCaption
{
    Q_OBJECT

public:
    explicit QTdInputMessageAudio(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setAttachmentPath(const QString &url);
    void setCaption(const QString &text);
    void setCaptionEntities(const QJsonArray &entities);

private:
    Q_DISABLE_COPY(QTdInputMessageAudio)
    QString m_audio;
    QString m_caption;
    QJsonArray m_captionEntities;
};

#endif // QTDINPUTMESSAGEAUDIO_H
