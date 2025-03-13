#ifndef QTDAUTHLOGOUTRESPONSE_H
#define QTDAUTHLOGOUTRESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdAuthLogOutResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1log_out.html
 */
class QTdAuthLogOutResponse : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdAuthLogOutResponse)
public:
    explicit QTdAuthLogOutResponse(QObject *parent = nullptr);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();
};

#endif // QTDAUTHLOGOUTRESPONSE_H
