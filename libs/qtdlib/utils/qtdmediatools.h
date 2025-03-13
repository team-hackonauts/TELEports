#ifndef QTDMEDIATOOLS_H
#define QTDMEDIATOOLS_H

#include <tuple>

#include <QObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include <QMediaPlayer>
#include <QPointer>

class QTdThumbnailExtractor : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdThumbnailExtractor)

public:
    explicit QTdThumbnailExtractor(QObject *parent = nullptr);
    std::tuple<QString, qint32, qint32> extractThumbnail(QString originalFile, qint32 maxSize);

private:
    QString m_originalFile;
};

class QTdMediaSizeExtractor : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMediaSizeExtractor)

public:
    explicit QTdMediaSizeExtractor(QObject *parent = nullptr);
    //TODO: This is to be implemented in a smarter way
    //std::tuple<qint32, qint32> extractVideoSize(QString videoPath);
    std::tuple<qint32, qint32> extractPictureSize(QString picturePath);
    Q_INVOKABLE bool canBeSendCompressed(QString picturePath);

private slots:
    void onMediaMetadataChanged();

private:
    bool m_stopMediaPlayer;
    QPointer<QMediaPlayer> fakeMediaPlayer;
};

#endif // QTDMEDIATOOLS_H