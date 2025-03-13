#ifndef QTDGETCHATSREQUEST_H
#define QTDGETCHATSREQUEST_H

#include <QObject>
#include <QtConcurrent>
#include <QString>
#include "common/qtdrequest.h"
#include "common/qtdresponse.h"

/**
 * @brief The QTdGetChatsRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_chats.html
 */
class QTdGetChatsRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdGetChatsRequest(QObject *parent = nullptr);

    void setChatList(const QString chatList);

    void setLimit(const qint64 value);

    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();

private:
    QString m_chatList;
    qint64 m_limit;
};

#endif // QTDGETCHATSREQUEST_H
