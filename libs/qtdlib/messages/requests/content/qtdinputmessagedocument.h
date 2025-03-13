#ifndef QTDINPUTMESSAGEDOCUMENT_H
#define QTDINPUTMESSAGEDOCUMENT_H

#include <QObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>

#include "../qtdinputmessagecontentattachmentcaption.h"

class QTdInputMessageDocument : public QTdInputMessageContentAttachmentCaption
{
    Q_OBJECT

public:
    explicit QTdInputMessageDocument(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setAttachmentPath(const QString &url);
    void setCaption(const QString &text);
    void setCaptionEntities(const QJsonArray &entities);

private:
    Q_DISABLE_COPY(QTdInputMessageDocument)
    QString m_document;
    QString m_caption;
    QJsonArray m_captionEntities;
};

#endif // QTDINPUTMESSAGEDOCUMENT_H
