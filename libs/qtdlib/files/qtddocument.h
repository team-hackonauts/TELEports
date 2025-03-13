#ifndef QTDDOCUMENT_H
#define QTDDOCUMENT_H

#include <QObject>
#include <QScopedPointer>
#include "common/qabstracttdobject.h"
#include "qtdthumbnail.h"

class QTdDocument : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName NOTIFY documentChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY documentChanged)
    Q_PROPERTY(QTdThumbnail *thumbnail READ thumbnail NOTIFY documentChanged)
    Q_PROPERTY(QTdFile *document READ document NOTIFY documentChanged)
public:
    explicit QTdDocument(QObject *parent = nullptr);

    QString fileName() const;

    QString mimeType() const;

    QTdThumbnail *thumbnail() const;

    QTdFile *document() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void documentChanged();

private:
    Q_DISABLE_COPY(QTdDocument)
    QString m_fileName;
    QString m_mimeType;
    QScopedPointer<QTdThumbnail> m_thumbnail;
    QScopedPointer<QTdFile> m_document;
};

#endif // QTDDOCUMENT_H
