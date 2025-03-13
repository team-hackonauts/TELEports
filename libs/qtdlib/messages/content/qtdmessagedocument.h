#ifndef QTDMESSAGEDOCUMENT_H
#define QTDMESSAGEDOCUMENT_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "files/qtddocument.h"
#include "qtdformattedtext.h"

class QTdMessageDocument : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdDocument *document READ document NOTIFY dataChanged)
    Q_PROPERTY(QTdFormattedText *caption READ caption NOTIFY dataChanged)
public:
    explicit QTdMessageDocument(QObject *parent = nullptr);

    QTdDocument *document() const;
    QTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessageDocument)
    QScopedPointer<QTdDocument> m_document;
    QScopedPointer<QTdFormattedText> m_caption;
};

#endif // QTDMESSAGEDOCUMENT_H
