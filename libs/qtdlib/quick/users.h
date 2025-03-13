#ifndef USERS_H
#define USERS_H

#include <QObject>
#include <QJsonObject>
#include "../user/qtduser.h"

class Users : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *model READ model NOTIFY modelChanged)
    Q_PROPERTY(QTdUser *me READ meMyself NOTIFY meChanged)
public:
    explicit Users(QObject *parent = nullptr);

    QObject *model() const;

    QTdUser *meMyself() const;

public slots:
    void deleteUser(const int &userId);
    void addUser(const QString &userName, const QString &firstName, const QString &lastName);
    void addContact(const QString &phoneNumber, const QString &firstName, const QString &lastName, const qint64 userId);

signals:
    void modelChanged();
    void meChanged();
};

#endif // USERS_H
