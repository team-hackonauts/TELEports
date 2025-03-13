#ifndef QTDMESSAGEPHOTO_H
#define QTDMESSAGEPHOTO_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "files/qtdphotos.h"
#include "qtdformattedtext.h"

class QTdMessagePhoto : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdPhotos *photo READ photo NOTIFY dataChanged)
    Q_PROPERTY(QTdFormattedText *caption READ caption NOTIFY dataChanged)
public:
    explicit QTdMessagePhoto(QObject *parent = nullptr);

    QTdPhotos *photo() const;
    QTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessagePhoto)
    QScopedPointer<QTdPhotos> m_photo;
    QScopedPointer<QTdFormattedText> m_caption;
};

#endif // QTDMESSAGEPHOTO_H
