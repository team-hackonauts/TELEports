#ifndef QTDREPORTCHATREQUEST_H
#define QTDREPORTCHATREQUEST_H

#include <QObject>
#include <QString>
#include "common/qabstracttdobject.h"
#include "common/qtdrequest.h"
#include "qtdchatreportreason.h"

class QTdReportChatRequest : public QTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdReportChatRequest)
public:
    explicit QTdReportChatRequest(QObject *parent = nullptr);

    void setChatId(const QString &id);
    void setMessageIds(const QList<qint64> &messageIds);
    void setReason(QTdChatReportReason *reason);
    void setText(const QString &text);
    QJsonObject marshalJson(); 

private:
    QString m_chatId;
    QList<qint64> m_messageIds;
    QTdChatReportReason *m_reason;
    QString m_text;

};

#endif // QTDREPORTCHATREQUEST_H
