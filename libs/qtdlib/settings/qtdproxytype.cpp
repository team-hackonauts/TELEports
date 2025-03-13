#include "common/qabstracttdobject.h"
#include "qtdproxytype.h"

QTdProxyType::QTdProxyType(QObject *parent)
    : QTdObject(parent)
{
}

QString QTdProxyType::username() const {
    return m_username;
}

void QTdProxyType::setUsername(QString value) {
    m_username = value;
}

QString QTdProxyType::password() const {
    return m_password;
}

void QTdProxyType::setPassword(QString value) {
    m_password = value;
}

QString QTdProxyType::secret() const
{
    return m_secret;
}

void QTdProxyType::setSecret(QString value) {
    m_secret = value;
}

bool QTdProxyType::httpOnly() const
{
    return m_httpOnly;
}

void QTdProxyType::setHttpOnly(bool value) {
    m_httpOnly = value;
}

int QTdProxyType::qmlType() const
{
    switch(type()) {
        case PROXY_TYPE_HTTP:
            return 0;
        case PROXY_TYPE_MTPROTO:
            return 1;
        case PROXY_TYPE_SOCKS5:
            return 2;
    }
    return -1;
}

QString QTdProxyType::typeString() const
{
    switch(type()) {
        case PROXY_TYPE_HTTP:
            return "HTTP";
        case PROXY_TYPE_MTPROTO:
            return "MTProto";
        case PROXY_TYPE_SOCKS5:
            return "SOCKS5";
    }
    return "";
}

QTdProxyType *QTdProxyType::create(const QJsonObject &json, QObject *parent) {
    const QString type = json["@type"].toString();
    QTdProxyType *proxyType = Q_NULLPTR;
    if (type == "proxyTypeHttp") {
        proxyType = new QTdProxyTypeHttp(parent);
    } else if (type == " proxyTypeMtproto") {
        proxyType = new QTdProxyTypeMtproto(parent);
    } else if (type == "proxyTypeSocks5") {
        proxyType = new QTdProxyTypeSocks5(parent);
    }
    if (proxyType != Q_NULLPTR) {
        proxyType->unmarshalJson(json);
    }
    return proxyType;
}

QJsonObject QTdProxyType::marshalJson()
{
    auto result = QJsonObject{
        { "username", m_username },
        { "password", m_password },
        { "secret", m_secret },
        { "http_only", m_httpOnly }
    };
    switch(type()) {
        case QTdObject::Type::PROXY_TYPE_HTTP:
            result["@type"] = "proxyTypeHttp";
            break;
        case QTdObject::Type::PROXY_TYPE_MTPROTO:
            result["@type"] = "proxyTypeMtproto";
            break;
        case QTdObject::Type::PROXY_TYPE_SOCKS5:
            result["@type"] = "proxyTypeSocks5";
            break;
    }
    return result;
}

void QTdProxyType::unmarshalJson(const QJsonObject &json)
{
    QTdObject::unmarshalJson(json);
    m_username = json["username"].toString();
    m_password = json["password"].toString();
    m_secret = json["secret"].toString();
    m_httpOnly = json["http_only"].toBool();
    emit dataChanged();
}

QTdProxyTypeHttp::QTdProxyTypeHttp(QObject *parent)
    : QTdProxyType(parent)
{
    setType(PROXY_TYPE_HTTP);
}

QTdProxyTypeMtproto::QTdProxyTypeMtproto(QObject *parent)
    : QTdProxyType(parent)
{
    setType(PROXY_TYPE_MTPROTO);
}

QTdProxyTypeSocks5::QTdProxyTypeSocks5(QObject *parent)
    : QTdProxyType(parent)
{
    setType(PROXY_TYPE_SOCKS5);
}
