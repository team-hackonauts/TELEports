#ifndef QTDMESSAGEAUDIO_H
#define QTDMESSAGEAUDIO_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "files/qtdaudio.h"
#include "qtdformattedtext.h"

class QTdMessageAudio : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdAudio *audio READ audio NOTIFY dataChanged)
    Q_PROPERTY(QTdFormattedText *caption READ caption NOTIFY dataChanged)
public:
    explicit QTdMessageAudio(QObject *parent = nullptr);

    QTdAudio *audio() const;
    QTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessageAudio)
    QScopedPointer<QTdAudio> m_audio;
    QScopedPointer<QTdFormattedText> m_caption;
};

#endif // QTDMESSAGEAUDIO_H
