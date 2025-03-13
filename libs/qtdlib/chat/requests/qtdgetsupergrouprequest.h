#ifndef QTDGETSUPERGROUPREQUEST_H
#define QTDGETSUPERGROUPREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdGetSuperGroupRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_supergroup.html
 */
class QTdGetSuperGroupRequest : public QTdRequest
{
    Q_OBJECT
    qint64 m_sgId;

public:
    explicit QTdGetSuperGroupRequest(QObject *parent = nullptr);
    void setSuperGroupId(const qint64 &id);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();
};

#endif // QTDGETSUPERGROUPREQUEST_H
