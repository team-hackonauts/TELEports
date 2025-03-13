#ifndef QTDBLOCKUSERREQUEST_H
#define QTDBLOCKUSERREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"
#include "user/qtduser.h"

/**
 * @brief The QTdBlockUserRequest class
 *
 * Add a user to the blacklist
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1block_user.html
 *
 * Usage:
 *
 *   QScopedPointer<QTdBlockUserRequest> req(new QTdBlockUserRequest);
 *   req->setUserId(1);
 *   // or
 *   req->setUserId("1");
 *   // or
 *   QTdUser *user;
 *   req->setUser(user);
 *   req->send();
 *   // or
 *   QFuture<QTdResponse> resp = req->sendAsync()
 *   await(resp)
 *   if (resp.result().isOk()) {}
 */
class QTdBlockUserRequest : public QTdOkRequest
{
    Q_OBJECT
public:
    explicit QTdBlockUserRequest(QObject *parent = nullptr);

    void setUser(QTdUser *user);
    void setUserId(const qint64 &id);
    void setUserId(const QString &id);

    QJsonObject marshalJson();

private:
    Q_DISABLE_COPY(QTdBlockUserRequest)
    qint64 m_userId;
};

#endif // QTDBLOCKUSERREQUEST_H
