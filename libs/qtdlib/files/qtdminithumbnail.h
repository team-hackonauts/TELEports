#ifndef QTDMINITHUMBNAIL_H
#define QTDMINITHUMBNAIL_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdMiniThumbnail : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString data READ data NOTIFY miniThumbnailChanged)
    Q_PROPERTY(QString dataURL READ dataURL NOTIFY miniThumbnailChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY miniThumbnailChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY miniThumbnailChanged)
public:
    explicit QTdMiniThumbnail(QObject *parent = nullptr);

    QString data() const;
    QString dataURL() const;
    qint32 width() const;
    qint32 height() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void miniThumbnailChanged();

private:
    Q_DISABLE_COPY(QTdMiniThumbnail)
    QString m_data;
    qint32 m_width;
    qint32 m_height;
};

#endif // QTDMINITHUMBNAIL_H
