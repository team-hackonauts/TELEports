#ifndef QTDINPUTMESSAGEVOICENOTE_H
#define QTDINPUTMESSAGEVOICENOTE_H

#include <QObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>

#include "imessageattachmentcontent.h"
#include "imessagecaptioncontent.h"
#include "../qtdinputmessagecontent.h"

class QTdInputMessageVoiceNote : public QTdInputMessageContent, public IMessageCaptionContent, public IMessageAttachmentContent
{
    Q_OBJECT
    Q_INTERFACES(IMessageCaptionContent IMessageAttachmentContent)

public:
    explicit QTdInputMessageVoiceNote(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setAttachmentPath(const QString &url);
    void setDuration(const qint32 &duration);
    void setWaveform(const QString &waveform);
    void setCaption(const QString &text);
    void setCaptionEntities(const QJsonArray &entities);

private:
    Q_DISABLE_COPY(QTdInputMessageVoiceNote)
    QString m_voiceNote;
    qint32 m_duration;
    QString m_waveform;
    QString m_caption;
    QJsonArray m_captionEntities;
};

#endif // QTDINPUTMESSAGEVOICENOTE_H
