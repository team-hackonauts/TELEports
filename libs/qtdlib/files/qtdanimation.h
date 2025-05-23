#ifndef QTDANIMATION_H
#define QTDANIMATION_H

#include <QObject>
#include <QScopedPointer>
#include "common/qabstracttdobject.h"
#include "qtdthumbnail.h"
#include "qtdminithumbnail.h"
#include "qtdfile.h"

/**
 * @brief The QTdAnimation class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1animation.html
 */
class QTdAnimation : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 duration READ duration NOTIFY animationChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY animationChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY animationChanged)
    Q_PROPERTY(QString fileName READ fileName NOTIFY animationChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY animationChanged)
    Q_PROPERTY(QTdThumbnail *thumbnail READ thumbnail NOTIFY animationChanged)
    Q_PROPERTY(QTdMiniThumbnail *miniThumbnail READ miniThumbnail NOTIFY animationChanged)
    Q_PROPERTY(QTdFile *animation READ animation NOTIFY animationChanged)
public:
    explicit QTdAnimation(QObject *parent = nullptr);

    qint32 duration() const;

    qint32 width() const;

    qint32 height() const;

    QString fileName() const;

    QString mimeType() const;

    QTdThumbnail *thumbnail() const;

    QTdMiniThumbnail *miniThumbnail() const;

    QTdFile *animation() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void animationChanged();

private:
    qint32 m_duration;
    qint32 m_width;
    qint32 m_height;
    QString m_fileName;
    QString m_mimeType;
    QScopedPointer<QTdThumbnail> m_thumbnail;
    QScopedPointer<QTdMiniThumbnail> m_minithumbnail;
    QScopedPointer<QTdFile> m_animation;
};

#endif // QTDANIMATION_H
