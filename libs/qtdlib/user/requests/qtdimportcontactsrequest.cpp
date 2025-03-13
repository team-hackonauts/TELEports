#include "qtdimportcontactsrequest.h"
#include "client/qtdclient.h"

QTdImportContactsRequest::QTdImportContactsRequest(QObject *parent)
    : QTdRequest(parent)
    , m_contacts(QJsonArray())
{
}

void QTdImportContactsRequest::setContacts(const QList<QTdContact *> &contacts)
{
    foreach (auto contact, contacts) {
        m_contacts.append(contact->marshalJson());
    }
}

QJsonObject QTdImportContactsRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "importContacts" },
        { "contacts", m_contacts }
    };
}

QFuture<QTdResponse> QTdImportContactsRequest::sendAsync()
{
    return QTdClient::instance()->sendAsync(this, &QTdClient::importedContacts);
}
