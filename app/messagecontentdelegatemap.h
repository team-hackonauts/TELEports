#ifndef MESSAGECONTENTDELEGATEMAP_H
#define MESSAGECONTENTDELEGATEMAP_H

#include <QObject>
#include <QHash>

class MessageContentDelegateMap : public QObject
{
    Q_OBJECT
public:
    explicit MessageContentDelegateMap(QObject *parent = Q_NULLPTR);

    Q_INVOKABLE QString findComponent(const int &type);

private:
    QHash<int, QString> m_delegates;
    QString m_default;
};

#endif // MESSAGECONTENTDELEGATEMAP_H
