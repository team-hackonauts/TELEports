#ifndef QTDAUTHDELETEACCOUNTRESPONSE_H
#define QTDAUTHDELETEACCOUNTRESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdAuthDeleteAccountResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1delete_account.html
 */
class QTdAuthDeleteAccountResponse : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdAuthDeleteAccountResponse)
public:
    explicit QTdAuthDeleteAccountResponse(QObject *parent = nullptr);

    /**
     * @brief setReason
     * @param reason
     *
     * (Optional) The reason why the account was deleted
     */
    void setReason(const QString &reason);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_reason;
};

#endif // QTDAUTHDELETEACCOUNTRESPONSE_H
