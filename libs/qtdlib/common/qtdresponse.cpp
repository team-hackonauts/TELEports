#include "qtdresponse.h"

QTdResponse::QTdResponse(QObject *parent)
{
}

bool QTdResponse::isError() const
{
    if (m_json.contains("@type")) {
        return m_json.value("@type").toString() == "error";
    }
    return false;
}

QString QTdResponse::errorString() const
{
    return isError() ? m_json.value("message").toString() : QString();
}

int QTdResponse::errorCode() const
{
    return isError() ? m_json.value("code").toInt() : 0;
}

bool QTdResponse::isOk() const
{
    if (m_json.contains("@type")) {
        return m_json.value("@type").toString() == "ok";
    }
    return false;
}

QJsonObject QTdResponse::json() const
{
    return m_json;
}

void QTdResponse::setJson(const QJsonObject &json)
{
    m_json = json;
}
