#ifndef QTDINPUTMESSAGECONTACT_H
#define QTDINPUTMESSAGECONTACT_H

#include <QObject>
#include <QScopedPointer>
#include <QJsonArray>
#include <QString>

#include "../qtdinputmessagecontent.h"
#include "../../../user/qtdcontact.h"

class QTdInputMessageContact : public QTdInputMessageContent
{
    Q_OBJECT
    
public:
    explicit QTdInputMessageContact(QObject *parent = nullptr);
    QJsonObject marshalJson();
    QTdContact *contact();

private:
    QScopedPointer<QTdContact> m_contact;
    Q_DISABLE_COPY(QTdInputMessageContact)
};

#endif // QTDINPUTMESSAGECONTACT_H
