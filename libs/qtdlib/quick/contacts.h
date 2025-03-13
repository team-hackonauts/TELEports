#ifndef CONTACTS_H
#define CONTACTS_H

#include <QObject>
#include <QJsonObject>
#include "../user/qtduser.h"

class Contacts : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)
    Q_PROPERTY(QTdUser* me READ meMyself NOTIFY meChanged)
public:
    explicit Contacts(QObject *parent = nullptr);

    QObject* model() const;

    QTdUser* meMyself() const;
signals:
    void modelChanged();
    void meChanged();
};

#endif // USERS_H
