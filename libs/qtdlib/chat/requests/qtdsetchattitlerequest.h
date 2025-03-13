#ifndef QTDSETCHATTITLEREQUEST_H
#define QTDSETCHATTITLEREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdSetChatTitleRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_chat_title.html
 */
class QTdSetChatTitleRequest : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdSetChatTitleRequest)
    QString m_title;
    qint64 m_chatId;

public:
    explicit QTdSetChatTitleRequest(QObject *parent = nullptr);

    void setTitle(const qint64 &chatId, const QString &title);
    QJsonObject marshalJson();
};

#endif // QTDSETCHATTITLEREQUEST_H
