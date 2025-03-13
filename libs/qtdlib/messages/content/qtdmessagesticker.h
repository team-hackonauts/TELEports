#ifndef QTDMESSAGESTICKER_H
#define QTDMESSAGESTICKER_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "files/qtdsticker.h"

class QTdMessageSticker : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdSticker *sticker READ sticker NOTIFY dataChanged)
    Q_PROPERTY(bool isPremium READ isPremium NOTIFY dataChanged)

public:
    explicit QTdMessageSticker(QObject *parent = nullptr);

    QTdSticker *sticker() const;

    bool isPremium() const;
    
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessageSticker)
    QScopedPointer<QTdSticker> m_sticker;
    bool m_is_premium;
};

#endif // QTDMESSAGESTICKER_H
