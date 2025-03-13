#ifndef QTDINPUTTHUMBNAIL_H
#define QTDINPUTTHUMBNAIL_H

#include <QObject>
#include <QJsonArray>
#include <QString>
#include <QScopedPointer>

#include "common/qabstracttdobject.h"
#include "../../../utils/qtdmediatools.h"

/**
 * @brief The QTdInputThumbnail class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1input_thumbnail.html
 */
class QTdInputThumbnail : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdInputThumbnail)

public:
    explicit QTdInputThumbnail(QObject *parent = nullptr);

    void setOriginalFile(QString filePath);
    qint32 width();
    qint32 height();
    QJsonObject marshalJson();

private:
    QString m_originalFile, m_thumbnailFile;
    qint32 m_width, m_height;
    QScopedPointer<QTdThumbnailExtractor> m_thumbnailExtractor;
};

#endif // QTDINPUTTHUMBNAIL_H