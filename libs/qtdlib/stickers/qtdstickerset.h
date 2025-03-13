#ifndef QTDSTICKERSET_H
#define QTDSTICKERSET_H

#include <QObject>
#include <QScopedPointer>
#include "models/QmlObjectListModel.h"
#include "common/qabstracttdobject.h"
#include "files/qtdthumbnail.h"
#include "files/qtdsticker.h"

class QTdStickerSet : public QTdObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY stickerSetChanged)
    Q_PROPERTY(QString title READ title NOTIFY stickerSetChanged)
    Q_PROPERTY(QTdThumbnail *thumbnail READ thumbnail NOTIFY stickerSetChanged)
    Q_PROPERTY(bool hasThumbnail READ hasThumbnail NOTIFY stickerSetChanged)
    Q_PROPERTY(bool isAnimated READ isAnimated NOTIFY stickerSetChanged)
    Q_PROPERTY(QObject *stickers READ qmlModel NOTIFY stickerSetChanged)
public:
    explicit QTdStickerSet(QObject *parent = nullptr);

    QString title() const;
    QString name() const;
    QTdThumbnail *thumbnail() const;
    bool hasThumbnail() const;
    bool isAnimated() const;

    QObject *qmlModel() const;

    Q_INVOKABLE void loadDetails() const;

    void handleDetails(const QJsonObject &json);

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void stickerSetChanged();

private:
    QScopedPointer<QQmlObjectListModel<QTdSticker>> m_stickers;
    QTdInt64 m_id;
    QString m_title;
    QString m_name;
    QScopedPointer<QTdThumbnail> m_thumbnail;
    QScopedPointer<QTdStickerFormat> m_format;
    QScopedPointer<QTdStickerType> m_type;
    bool m_hasThumbnail;
    bool m_isAnimated;
    bool m_detailsLoaded;
    bool m_isInstalled;
    bool m_isArchived;
    bool m_isOfficial;
};

#endif // QTDSTICKERSET_H
