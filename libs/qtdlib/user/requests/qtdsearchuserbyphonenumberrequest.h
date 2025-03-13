#ifndef QTDSEARCHUSERBYPHONENUMBERREQUEST_H
#define QTDSEARCHUSERBYPHONENUMBERREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"
#include "user/qtduser.h"

class QTdSearchUserByPhoneNumberRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdSearchUserByPhoneNumberRequest(QObject *parent = nullptr);

    void setPhoneNumber(const QString &value);

    QJsonObject marshalJson() Q_DECL_FINAL;
    QFuture<QTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QTdSearchUserByPhoneNumberRequest)
    QString m_phoneNumber;
};

#endif // QTDSEARCHUSERBYPHONENUMBERREQUEST_H
