#ifndef QTDGETSUPERGROUPFULLINFOREQUEST_H
#define QTDGETSUPERGROUPFULLINFOREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdGetSuperGroupFullInfoRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_supergroup_full_info.html
 */
class QTdGetSuperGroupFullInfoRequest : public QTdRequest
{
    Q_OBJECT
    qint64 m_id;

public:
    explicit QTdGetSuperGroupFullInfoRequest(QObject *parent = nullptr);

    void setSupergroupId(const qint64 &id);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();
};

#endif // QTDGETSUPERGROUPFULLINFOREQUEST_H
