#ifndef QTDREQUEST_H
#define QTDREQUEST_H

#include <QObject>
#include <QtConcurrent>
#include "qabstracttdobject.h"
#include "qtdresponse.h"

/**
 * @brief The QTdRequest class
 *
 * Base class for all rdlib requests
 */
class QTdRequest : public QTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdRequest)
public:
    explicit QTdRequest(QObject *parent = nullptr);

    virtual QFuture<QTdResponse> sendAsync() = 0;
    virtual void send();
    virtual QFuture<QJsonObject> exec();
};

/**
 * @brief The QTdOkRequest class
 *
 * A request class that expects an OK response from tdlib
 * for the requested action
 */
class QTdOkRequest : public QTdRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdOkRequest)
public:
    explicit QTdOkRequest(QObject *parent = nullptr);
    /**
     * @brief sendAsync
     * @return QTdResponse - will either be resp.isOk() or resp.isError()
     */
    QFuture<QTdResponse> sendAsync();
};

#endif // QTDREQUEST_H
