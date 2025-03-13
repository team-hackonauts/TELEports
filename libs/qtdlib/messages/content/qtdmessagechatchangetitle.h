#ifndef QTDMESSAGECHATCHANGETITLE_H
#define QTDMESSAGECHATCHANGETITLE_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessageChatChangeTitle : public QTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageChatChangeTitle)
    Q_PROPERTY(QString title READ title NOTIFY contentChanged)
public:
    explicit QTdMessageChatChangeTitle(QObject *parent = nullptr);

    QString title() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    QString m_title;
};

#endif // QTDMESSAGECHATCHANGETITLE_H
