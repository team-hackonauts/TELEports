#ifndef QTDMESSAGEANIMATION_H
#define QTDMESSAGEANIMATION_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "files/qtdanimation.h"
#include "qtdformattedtext.h"

class QTdMessageAnimation : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdAnimation *animation READ animation NOTIFY dataChanged)
    Q_PROPERTY(QTdFormattedText *caption READ caption NOTIFY dataChanged)
public:
    explicit QTdMessageAnimation(QObject *parent = nullptr);

    QTdAnimation *animation() const;
    QTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessageAnimation)
    QScopedPointer<QTdAnimation> m_animation;
    QScopedPointer<QTdFormattedText> m_caption;
};

#endif // QTDMESSAGEANIMATION_H
