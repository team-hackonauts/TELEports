#include "qtdinputmessagecontact.h"

QTdInputMessageContact::QTdInputMessageContact(QObject *parent)
    : QTdInputMessageContent(parent)
    , m_contact(new QTdContact(this))
{
}

QTdContact *QTdInputMessageContact::contact() {
    return m_contact.data();
}

QJsonObject QTdInputMessageContact::marshalJson()
{
    return QJsonObject{
        { "@type", "inputMessageContact" },
        { "contact", m_contact->marshalJson() }
    };
}
