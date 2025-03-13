#ifndef QTDMESSAGEPINMESSAGE_H
#define QTDMESSAGEPINMESSAGE_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessagePinMessage : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(qint64 message_id READ message_id NOTIFY dataChanged)
public:
    explicit QTdMessagePinMessage(QObject *parent = nullptr);

    qint64 message_id() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QTdMessagePinMessage)
    qint64 m_message_id;
};

#endif // QTDMESSAGEPINMESSAGE_H
