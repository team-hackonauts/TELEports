#ifndef QTDREMOVECONTACTSREQUEST_H
#define QTDREMOVECONTACTSREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"
#include "user/qtduser.h"

class QTdRemoveContactsRequest : public QTdOkRequest
{
    Q_OBJECT
public:
    explicit QTdRemoveContactsRequest(QObject *parent = nullptr);

    void setUserIds(const QList<qint64> &userIds);
    QJsonObject marshalJson();

private:
    Q_DISABLE_COPY(QTdRemoveContactsRequest)
    QList<qint64> m_userIds;
};

#endif // QTDREMOVECONTACTSREQUEST_H
