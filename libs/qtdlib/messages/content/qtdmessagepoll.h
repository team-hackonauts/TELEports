#ifndef QTDMESSAGEPOLL_H
#define QTDMESSAGEPOLL_H

#include <QObject>
#include <QPointer>
#include "messages/qtdmessagecontent.h"
#include "qtdpoll.h"

class QTdMessagePoll : public QTdMessageContent
{
    Q_OBJECT

    Q_PROPERTY(QTdPoll *poll READ poll NOTIFY dataChanged)

public:
    explicit QTdMessagePoll(QObject *parent = nullptr);

    QTdPoll *poll();
    
    void unmarshalJson(const QJsonObject &json);

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessagePoll)
    QScopedPointer<QTdPoll> m_poll;
};

#endif // QTDMESSAGEPOLL_H