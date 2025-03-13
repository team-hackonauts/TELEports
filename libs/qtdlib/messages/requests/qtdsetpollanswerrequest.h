#ifndef QTDSETPOLLANSWERREQUEST_H
#define QTDSETPOLLANSWERREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdSetPollAnswerRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_poll_answer.html
 */
class QTdSetPollAnswerRequest : public QTdOkRequest
{
    Q_OBJECT
    qint64 m_chatId;
    qint64 m_messageId;
    QList<qint32> m_optionIds;

public:
    explicit QTdSetPollAnswerRequest(QObject *parent = nullptr);
    void setMessageId(const qint64 &messageId);
    void setPollOptions(const QList<qint32> &optionIds);
    void setChatId(const qint64 &id);
    QJsonObject marshalJson() Q_DECL_FINAL;
};

#endif // QTDSETPOLLANSWERREQUEST_H
