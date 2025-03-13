#ifndef QTDGETCONTACTSREQUEST_H
#define QTDGETCONTACTSREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"
#include "common/qtdint.h"

/**
 * @brief The QTdGetUserRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_contacts.html
 */
class QTdGetContactsRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdGetContactsRequest(QObject *parent = nullptr);

    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();

};

#endif // QTDGETCONTACTSREQUEST_H
