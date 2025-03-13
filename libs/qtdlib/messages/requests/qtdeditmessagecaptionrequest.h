#ifndef QTDEDITMESSAGECAPTIONREQUEST_H
#define QTDEDITMESSAGECAPTIONREQUEST_H

#include <QObject>
#include <QJsonArray>

#include "common/qtdrequest.h"

class QTdEditMessageCaptionRequest : public QTdRequest
{
    Q_OBJECT
    qint64 m_chatId;
    qint64 m_messageId;
    QString m_text;
    QJsonArray m_entities;

public:
    explicit QTdEditMessageCaptionRequest(QObject *parent = nullptr);
    void setText(const QString &text);
    void setChatId(const qint64 &id);
    void setMessageId(const qint64 &id);
    void setEntities(const QJsonArray &entities);
    QJsonObject marshalJson();
    virtual QFuture<QTdResponse> sendAsync();
};

#endif // QTDEDITMESSAGECAPTIONREQUEST_H
