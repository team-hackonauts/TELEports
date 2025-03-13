#ifndef QTDMESSAGEDATE_H
#define QTDMESSAGEDATE_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessageDate : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QDateTime date READ date NOTIFY dataChanged)
    Q_PROPERTY(QString dateString READ dateString NOTIFY dataChanged)
public:
    explicit QTdMessageDate(QObject *parent = nullptr);

    QDateTime date() const;
    QString dateString() const;

    void setDate(const qint32 &date);

signals:
    void dataChanged();

private:
    qint32 m_date;
};

#endif // QTDMESSAGEDATE_H
