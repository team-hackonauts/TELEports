#ifndef QTDCHATPOSITION_H
#define QTDCHATPOSITION_H

#include <QObject>
#include <QPointer>
#include "qtdchatlist.h"
#include "common/qabstractint64id.h"

class QTdChatPosition : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatPosition)

    Q_PROPERTY(QObject *list READ list NOTIFY listChanged)
    Q_PROPERTY(QString order READ qmlOrder NOTIFY orderChanged)
    Q_PROPERTY(bool isPinned READ isPinned NOTIFY isPinnedChanged)
    // Q_PROPERTY(QString source READ source NOTIFY sourceChanged)

public:
    explicit QTdChatPosition(QObject *parent = nullptr);
    void unmarshalJson(const QJsonObject &json) override;

    QTdChatList *list() const;
    QString qmlOrder() const;
    qint64 order() const;
    bool isPinned() const;
    // QTdChatSource *source() const;

signals:
    void listChanged();
    void orderChanged();
    void isPinnedChanged();
    void sourceChanged();

private:
    QScopedPointer<QTdChatList> m_list;
    QTdInt64 m_order;
    bool m_isPinned;
    // QPointer<QTdChatSource> m_source
};

#endif // QTDCHATPOSITION_H
