#ifndef AUXDB_H
#define AUXDB_H

#include <QFile>
#include <QObject>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(auxdb)

class AvatarMapTable;

const qint64 INVALID_ID = -1;

class AuxDatabase : public QObject
{
    Q_OBJECT

public:
    AuxDatabase(QString dbDirectory, QString schemaDirectory, QObject *parent = 0);

    ~AuxDatabase();

    void logSqlError(QSqlQuery &q) const;
    QSqlDatabase *getDB();

    AvatarMapTable *getAvatarMapTable() const;

private:
    bool openDB();

    int schemaVersion() const;
    void setSchemaVersion(int version);
    void upgradeSchema(int current_version);

    bool executeSqlFile(QFile &file);

    const QString &getSqlDir() const;

    QString getDBname() const;
    QString getDBBackupName() const;

    QString m_databaseDirectory;
    QString m_sqlSchemaDirectory;
    QSqlDatabase *m_db;
    AvatarMapTable *m_avatarMapTable;
};

#endif // AUXDB_H
