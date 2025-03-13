#ifndef QTDMESSAGEUNREADLABEL_H
#define QTDMESSAGEUNREADLABEL_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessageUnreadLabel : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label NOTIFY labelChanged)

public:
    explicit QTdMessageUnreadLabel(QObject *parent = nullptr);

    void setLabel(const QString label);
    QString label();

signals:
    void labelChanged();

private:
    QString m_label;
};

#endif // QTDMESSAGEUNREADLABEL_H
