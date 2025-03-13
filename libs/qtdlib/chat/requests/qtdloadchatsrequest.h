#ifndef QTDLOADCHATSREQUEST_H
#define QTDLOADCHATSREQUEST_H

#include <QObject>
#include <QtConcurrent>
#include <QString>
#include "common/qtdrequest.h"
#include "common/qtdresponse.h"

/**
 * @brief The QTdGetChatsRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1load_chats.html
 */
class QTdLoadChatsRequest : public QTdOkRequest
{
    Q_OBJECT
public:
    explicit QTdLoadChatsRequest(QObject *parent = nullptr);

    void setChatList(const QString chatList);

    void setLimit(const qint64 value);

    QJsonObject marshalJson();

private:
    QString m_chatList;
    qint64 m_limit;
};

#endif // QTDLOADCHATSREQUEST_H
