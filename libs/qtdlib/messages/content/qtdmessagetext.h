#ifndef QTDMESSAGETEXT_H
#define QTDMESSAGETEXT_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "qtdformattedtext.h"
#include "qtdwebpage.h"

class QTdMessageText : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdFormattedText *text READ text NOTIFY dataChanged)
    Q_PROPERTY(QTdWebPage *webPage READ webPage NOTIFY dataChanged)
public:
    explicit QTdMessageText(QObject *parent = nullptr);

    QTdFormattedText *text() const;
    QTdWebPage *webPage() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessageText)
    QScopedPointer<QTdFormattedText> m_text;
    QScopedPointer<QTdWebPage> m_webPage;
    bool m_hasWebPage;
};

#endif // QTDMESSAGETEXT_H
