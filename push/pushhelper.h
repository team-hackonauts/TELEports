#ifndef PUSH_HELPER_H
#define PUSH_HELPER_H

#include <QObject>
#include <QJsonObject>
#include <QHash>
#include <QPointer>
#include "../common/auxdb/auxdb.h"
#include "../common/auxdb/postal-client.h"

class PushHelper : public QObject
{
    Q_OBJECT

public:
    PushHelper(const QString appId, const QString infile, const QString outfile, QObject *parent = 0);
    ~PushHelper() = default;
    void process();

Q_SIGNALS:
    void done();
    
protected:
    QJsonObject readPushMessage(const QString &filename);
    void writePostalMessage(const QJsonObject &postalMessage, const QString &filename);
    QJsonObject pushToPostalMessage(const QJsonObject &push);

private:
    QString mInfile;
    QString mOutfile;
    QJsonObject mPostalMessage;
    AuxDatabase m_auxdb;
    QScopedPointer<PostalClient> m_postalClient;
};

#endif
