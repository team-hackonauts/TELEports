#ifndef QTDMESSAGEVIDEO_H
#define QTDMESSAGEVIDEO_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "files/qtdvideo.h"
#include "qtdformattedtext.h"

class QTdMessageVideo : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdVideo *video READ video NOTIFY dataChanged)
    Q_PROPERTY(QTdFormattedText *caption READ caption NOTIFY dataChanged)
public:
    explicit QTdMessageVideo(QObject *parent = nullptr);

    QTdVideo *video() const;
    QTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessageVideo)
    QScopedPointer<QTdVideo> m_video;
    QScopedPointer<QTdFormattedText> m_caption;
};

#endif // QTDMESSAGEVIDEO_H
