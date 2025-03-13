#include "contacts.h"
#include <QDebug>
#include "user/qtdusers.h"

Contacts::Contacts(QObject *parent)
    : QObject(parent)
{
    emit modelChanged();
    connect(QTdUsers::instance(), &QTdUsers::meMyselfChanged, this, &Contacts::meChanged);
}

QObject *Contacts::model() const
{
    return QTdUsers::instance()->contactsmodel();
}

QTdUser *Contacts::meMyself() const
{
    return QTdUsers::instance()->meMyself();
}
