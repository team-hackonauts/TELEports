#ifndef QTDSETPINNEDCHATSREQUEST_H
#define QTDSETPINNEDCHATSREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdSetPinnedChatsRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_pinned_chats.html
 */
class QTdSetPinnedChatsRequest : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdSetPinnedChatsRequest)
    QList<qint64> m_chatIds;

public:
    explicit QTdSetPinnedChatsRequest(QObject *parent = nullptr);

    void setPinnedChats(const QList<qint64> &chatIds);
    QJsonObject marshalJson();
};

#endif // QTDSETPINNEDCHATSREQUEST_H
