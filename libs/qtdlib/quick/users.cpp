#include "users.h"
#include <QDebug>
#include "user/qtdusers.h"

Users::Users(QObject *parent)
    : QObject(parent)
{
    emit modelChanged();
    connect(QTdUsers::instance(), &QTdUsers::meMyselfChanged, this, &Users::meChanged);
}

QObject *Users::model() const
{
    return QTdUsers::instance()->model();
}

QTdUser *Users::meMyself() const
{
    return QTdUsers::instance()->meMyself();
}

void Users::deleteUser(const int &userId)
{
    QTdUsers::instance()->deleteUser(userId);
}

void Users::addUser(const QString &userName, const QString &firstName, const QString &lastName)
{
    QTdUsers::instance()->addUser(userName, firstName, lastName);
}

void Users::addContact(const QString &phoneNumber, const QString &firstName, const QString &lastName, const qint64 userId) {
    QTdUsers::instance()->addContact(phoneNumber, firstName, lastName, userId);
}