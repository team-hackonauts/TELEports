#ifndef QTDRESPONSE_H
#define QTDRESPONSE_H

#include <QObject>
#include <QJsonObject>

/**
 * @brief The QTdResponse class
 */
class QTdResponse
{
public:
    explicit QTdResponse(QObject *parent = nullptr);

    /**
     * @brief isError
     * @return bool - if response is of type "error"
     *
     * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1error.html
     */
    bool isError() const;

    /**
     * @brief errorString
     * @return QString - the returned error message
     */
    QString errorString() const;

    /**
     * @brief errorCode
     * @return int - the returned error code
     */
    int errorCode() const;

    /**
     * @brief isOk
     * @return bool - if response is of type "ok"
     *
     * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1ok.html
     */
    bool isOk() const;

    /**
     * @brief json
     * @return QJsonObject  - the raw recieved json data
     */
    QJsonObject json() const;

    /**
     * @brief setJson
     * @param json - set the response data
     */
    void setJson(const QJsonObject &json);

private:
    QJsonObject m_json;
};

#endif // QTDRESPONSE_H
