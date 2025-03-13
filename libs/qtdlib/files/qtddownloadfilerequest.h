#ifndef QTDDOWNLOADFILEREQUEST_H
#define QTDDOWNLOADFILEREQUEST_H

#include <QObject>
#include "common/qtdrequest.h"

/**
 * @brief The QTdDownloadFileRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1download_file.html
 */
class QTdDownloadFileRequest : public QTdRequest
{
    Q_OBJECT
public:
    explicit QTdDownloadFileRequest(QObject *parent = nullptr);

    enum Priority {
        Low = 1,
        Medium = 16,
        High = 32
    };
    Q_ENUM(Priority)

    void setPriority(const Priority &priority);
    void setFileId(const qint64 &fileId);

    QJsonObject marshalJson();

    QFuture<QTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QTdDownloadFileRequest)
    Priority m_priority;
    qint64 m_fileId;
};

#endif // QTDDOWNLOADFILEREQUEST_H
