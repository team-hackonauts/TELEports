#ifndef QTDSTICKER_H
#define QTDSTICKER_H

#include <QObject>
#include <QScopedPointer>
#include "common/qabstracttdobject.h"
#include "common/qtdint.h"
#include "qtdthumbnail.h"
#include "sticker/qtdstickerformat.h"
#include "sticker/qtdstickertype.h"

class QTdSticker : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString setId READ qmlSetId NOTIFY stickerChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY stickerChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY stickerChanged)
    Q_PROPERTY(QString emoji READ emoji NOTIFY stickerChanged)
    Q_PROPERTY(QTdStickerType* stickerType READ qmlType NOTIFY stickerChanged)
    Q_PROPERTY(QTdStickerFormat* stickerFormat READ qmlFormat NOTIFY stickerChanged)
    Q_PROPERTY(bool isMask READ isMask NOTIFY stickerChanged)
    // TODO: Q_PROPERTY(QTdMaskPosition maskPosition READ maskPosition NOTIFY stickerChanged)
    Q_PROPERTY(QTdThumbnail *thumbnail READ thumbnail NOTIFY stickerChanged)
    Q_PROPERTY(QTdFile *sticker READ sticker NOTIFY stickerChanged)
public:
    explicit QTdSticker(QObject *parent = nullptr);

    QString qmlSetId() const;
    qint64 setId() const;

    qint32 width() const;

    qint32 height() const;

    QString emoji() const;

    QTdStickerType *qmlType() const;
    QTdStickerFormat *qmlFormat() const;

    bool isMask() const;

    QTdFile *sticker() const;

    void unmarshalJson(const QJsonObject &json) override;

    QTdThumbnail *thumbnail() const;

signals:
    void stickerChanged();

private:
    QTdInt64 m_setId;
    qint32 m_width;
    qint32 m_height;
    QString m_emoji;
    QScopedPointer<QTdStickerFormat> m_format;
    QScopedPointer<QTdStickerType> m_type;
    bool m_isMask;
    QScopedPointer<QTdThumbnail> m_thumbnail;
    QScopedPointer<QTdFile> m_sticker;
};

#endif // QTDSTICKER_H
