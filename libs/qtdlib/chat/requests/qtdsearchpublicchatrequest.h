#ifndef QTDSEARCHPUBLICCHATREQUEST_H
#define QTDSEARCHPUBLICCHATREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdSearchPublicChatRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1search_public_chat.html
 */
class QTdSearchPublicChatRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdSearchPublicChatRequest(QObject *parent = nullptr);

    void setChatUsername(const QString &username);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();

private:
    QString m_username;
};

#endif // QTDSEARCHPUBLICCHATREQUEST_H
