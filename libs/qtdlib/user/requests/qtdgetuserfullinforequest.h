#ifndef QTDGETUSERFULLINFOREQUEST_H
#define QTDGETUSERFULLINFOREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"
#include "common/qtdint.h"

/**
 * @brief The QTdGetUserRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_user.html
 */
class QTdGetUserFullInfoRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdGetUserFullInfoRequest(QObject *parent = nullptr);

    void setUserId(const QString &id);
    void setUserId(const qint64 &id);

    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();

private:
    QTdInt64 m_uid;
};

#endif // QTDGETUSERFULLINFOREQUEST_H
