#ifndef QTdVoiceNote_H
#define QTdVoiceNote_H

#include <QObject>
#include <QScopedPointer>
#include "common/qabstracttdobject.h"
#include "qtdphotosize.h"

class QTdVoiceNote : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 duration READ duration NOTIFY voiceNoteChanged)
    Q_PROPERTY(QString waveform READ waveform NOTIFY voiceNoteChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY voiceNoteChanged)
    Q_PROPERTY(QTdFile *voice READ voice NOTIFY voiceNoteChanged)
    Q_PROPERTY(QString qmlDuration READ qmlDuration NOTIFY voiceNoteChanged)
public:
    explicit QTdVoiceNote(QObject *parent = nullptr);

    qint32 duration() const;

    QString waveform() const;

    QString mimeType() const;

    QTdFile *voice() const;

    QString qmlDuration() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void voiceNoteChanged();

private:
    qint32 m_duration;
    QString m_waveform;
    QString m_mimeType;
    QScopedPointer<QTdFile> m_voice;
};

#endif // QTdVoiceNote_H
