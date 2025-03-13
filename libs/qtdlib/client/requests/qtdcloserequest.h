#ifndef QTDCLOSEREQUEST_H
#define QTDCLOSEREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdCloseRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close.html
 */
class QTdCloseRequest : public QTdOkRequest
{
    Q_OBJECT

public:
    explicit QTdCloseRequest(QObject *parent = nullptr);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

};

#endif // QTDCLOSEREQUEST_H
