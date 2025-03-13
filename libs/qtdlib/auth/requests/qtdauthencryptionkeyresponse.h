#ifndef QTDAUTHENCRYPTIONKEYRESPONSE_H
#define QTDAUTHENCRYPTIONKEYRESPONSE_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdAuthEncryptionKeyResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_database_encryption_key.html
 */
class QTdAuthEncryptionKeyResponse : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdAuthEncryptionKeyResponse)
public:
    explicit QTdAuthEncryptionKeyResponse(QObject *parent = nullptr);

    /**
     * @brief setKey
     * @param key - New encryption key
     */
    void setKey(const QString &key);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_key;
};

#endif // QTDAUTHENCRYPTIONKEYRESPONSE_H
