#ifndef QTDSENDMESSAGEALBUMREQUEST_H
#define QTDSENDMESSAGEALBUMREQUEST_H

#include <QObject>
#include <QJsonArray>
#include <QScopedPointer>
#include <QList>

#include "common/qtdrequest.h"
#include "qtdinputmessagecontent.h"
#include "qtdmessagesendoptions.h"

/**
 * @brief The QTdSendMessageAlbumRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1send_message_album.html
 */
class QTdSendMessageAlbumRequest : public QTdRequest
{
    Q_OBJECT

public:
    explicit QTdSendMessageAlbumRequest(QObject *parent = nullptr);
    void setContents(QList<QTdInputMessageContent*> &contents);
    void setChatId(const qint64 &id);
    void setReplyToMessageId(const qint64 &id);
    void setDisableNotification(const bool value);
    void setSendDate(const qint32 value);
    QJsonObject marshalJson();
    QFuture<QTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QTdSendMessageAlbumRequest)
    qint64 m_chatId;
    qint64 m_replyMessageId;
    QList<QTdInputMessageContent*> m_contents;
    QScopedPointer<QTdMessageSendOptions> m_messageSendOptions;

};

#endif // QTDSENDMESSAGEALBUMREQUEST_H
