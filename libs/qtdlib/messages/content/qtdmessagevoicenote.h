#ifndef QTDMESSAGEVOICENOTE_H
#define QTDMESSAGEVOICENOTE_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "files/qtdvoicenote.h"
#include "qtdformattedtext.h"

class QTdMessageVoiceNote : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdVoiceNote *voiceNote READ voiceNote NOTIFY dataChanged)
    Q_PROPERTY(QTdFormattedText *caption READ caption NOTIFY dataChanged)
    Q_PROPERTY(bool isListened READ isListened NOTIFY dataChanged)
public:
    explicit QTdMessageVoiceNote(QObject *parent = nullptr);

    QTdVoiceNote *voiceNote() const;
    QTdFormattedText *caption() const;
    bool isListened() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessageVoiceNote)
    QScopedPointer<QTdVoiceNote> m_voiceNote;
    QScopedPointer<QTdFormattedText> m_caption;
    bool m_isListened;
};

#endif // QTDMESSAGEVOICENOTE_H
