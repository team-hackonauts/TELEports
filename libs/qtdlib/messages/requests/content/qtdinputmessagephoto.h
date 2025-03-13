#ifndef QTDINPUTMESSAGEPHOTO_H
#define QTDINPUTMESSAGEPHOTO_H

#include <QObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include <QScopedPointer>

#include "../qtdinputmessagecontentattachmentcaption.h"
#include "qtdinputthumbnail.h"
#include "../../../utils/qtdmediatools.h"

class QTdInputMessagePhoto : public QTdInputMessageContentAttachmentCaption
{
    Q_OBJECT

public:
    explicit QTdInputMessagePhoto(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setAttachmentPath(const QString &url);
    void setCaption(const QString &text);
    void setCaptionEntities(const QJsonArray &entities);

private:
    Q_DISABLE_COPY(QTdInputMessagePhoto)
    QString m_photo;
    qint32 m_width, m_height;
    QString m_caption;
    QJsonArray m_captionEntities;
    QScopedPointer<QTdMediaSizeExtractor> m_mediaSizeExtractor;
    QScopedPointer<QTdInputThumbnail> m_inputThumbnail;
};

#endif // QTDINPUTMESSAGEPHOTO_H
