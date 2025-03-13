#ifndef QTDIMPORTCONTACTSREQUEST_H
#define QTDIMPORTCONTACTSREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"
#include "common/qtdint.h"
#include "../qtdcontact.h"

/**
 * @brief The QTdGetUserRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_contacts.html
 */
class QTdImportContactsRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdImportContactsRequest(QObject *parent = nullptr);

    void setContacts(const QList<QTdContact *> &contacts);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QTdImportContactsRequest)
    QJsonArray m_contacts;
};

#endif // QTDIMPORTCONTACTSREQUEST_H
