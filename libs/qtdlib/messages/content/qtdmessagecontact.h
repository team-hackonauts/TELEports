#ifndef QTDMESSAGECONTACT_H
#define QTDMESSAGECONTACT_H

#include <QObject>
#include <QScopedPointer>
#include "messages/qtdmessagecontent.h"
#include "../../user/qtdcontact.h"

class QTdMessageContact : public QTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QTdContact* contact READ contact NOTIFY dataChanged)

public:
    explicit QTdMessageContact(QObject *parent = nullptr);

    QTdContact *contact() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();
    
private:
    Q_DISABLE_COPY(QTdMessageContact)
    QScopedPointer<QTdContact> m_contact;
};

#endif // QTDMESSAGECONTACT_H

