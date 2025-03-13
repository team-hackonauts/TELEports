#ifndef QTDPROXYTYPE_H
#define QTDPROXYTYPE_H

#include <QObject>

class QTdProxyType: public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY dataChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY dataChanged)
    Q_PROPERTY(QString secret READ secret WRITE setSecret NOTIFY dataChanged)
    Q_PROPERTY(int type READ qmlType NOTIFY dataChanged)
    Q_PROPERTY(QString typeString READ typeString NOTIFY dataChanged)
    Q_PROPERTY(bool httpOnly READ httpOnly WRITE setHttpOnly NOTIFY dataChanged)

public:

    explicit QTdProxyType(QObject *parent = nullptr);
    static QTdProxyType *create(const QJsonObject &json, QObject *parent);
    QJsonObject marshalJson();
    void unmarshalJson(const QJsonObject &json) override;

    int qmlType() const;
    QString typeString() const;
    QString username() const;
    void setUsername(QString value);
    QString password() const;
    void setPassword(QString value);
    QString secret() const;
    void setSecret(QString value);
    bool httpOnly() const;
    void setHttpOnly(bool value);

signals:
    void dataChanged();

protected:
    QString m_username;
    QString m_password;
    QString m_secret;
    bool m_httpOnly;
};

class QTdProxyTypeHttp: public QTdProxyType
{
    Q_OBJECT
public:
    explicit QTdProxyTypeHttp(QObject *parent = nullptr);

};

class QTdProxyTypeMtproto: public QTdProxyType
{
    Q_OBJECT
public:
    explicit QTdProxyTypeMtproto(QObject *parent = nullptr);
};

class QTdProxyTypeSocks5: public QTdProxyType
{
    Q_OBJECT
public:
    explicit QTdProxyTypeSocks5(QObject *parent = nullptr);
};

#endif // QTDPROXYTYPE_H