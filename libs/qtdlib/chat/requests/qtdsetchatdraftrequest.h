#ifndef QTDSETCHATDRAFTREQUEST_H
#define QTDSETCHATDRAFTREQUEST_H

#include <QObject>
#include <QJsonArray>

#include "common/qtdrequest.h"
#include "messages/qtddraftmessage.h"

/**
 * @brief The QTdSetChatDraftRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_chat_draft_message.html
 */
class QTdSetChatDraftRequest : public QTdRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdSetChatDraftRequest)
    qint64 m_chatId;
    QScopedPointer<QTdDraftMessage> m_draftMessage;

public:
    explicit QTdSetChatDraftRequest(QObject *parent = nullptr);
    void setDraftMessage(QTdDraftMessage *draftMessage);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();
};

#endif // QTDSETCHATDRAFTREQUEST_H
