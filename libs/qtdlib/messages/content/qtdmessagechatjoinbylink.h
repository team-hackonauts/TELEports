#ifndef QTDMESSAGECHATJOINBYLINK_H
#define QTDMESSAGECHATJOINBYLINK_H

#include <QObject>
#include "messages/qtdmessagecontent.h"

/**
 * @brief The QTdMessageChatJoinByLink class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_chat_join_by_link.html
 */
class QTdMessageChatJoinByLink : public QTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdMessageChatJoinByLink)
public:
    explicit QTdMessageChatJoinByLink(QObject *parent = nullptr);
};

#endif // QTDMESSAGECHATJOINBYLINK_H
