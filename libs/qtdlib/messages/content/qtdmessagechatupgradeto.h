#ifndef QTDMESSAGECHATUPGRADETO_H
#define QTDMESSAGECHATUPGRADETO_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

class QTdMessageChatUpgradeTo : public QTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageChatUpgradeTo)
    Q_PROPERTY(QString superGroupId READ qmlSuperGroupId NOTIFY contentChanged)
public:
    explicit QTdMessageChatUpgradeTo(QObject *parent = nullptr);

    QString qmlSuperGroupId() const;

    qint64 superGroupId() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    QTdInt64 m_sgId;
};

#endif // QTDMESSAGECHATUPGRADETO_H
