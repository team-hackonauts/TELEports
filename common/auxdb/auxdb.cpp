#include "auxdb.h"
#include "avatarmaptable.h"

#include <QFile>
#include <QSqlTableModel>
#include <QtSql>
#include <QDir>

Q_LOGGING_CATEGORY(auxdb, "auxdb")

/*!
 * \brief Database::Database
 * \param databaseDir directory to load/store the database
 * \param schemaDirectory directory of the SQL schema for the database
 * \param parent
 */
AuxDatabase::AuxDatabase(QString dbDirectory, QString schemaDirectory, QObject *parent)
    : QObject(parent)
    , m_databaseDirectory(dbDirectory)
    , m_sqlSchemaDirectory(schemaDirectory)
    , m_db(new QSqlDatabase())
{
    if (!QFile::exists(m_databaseDirectory)) {
        QDir dir;
        bool createOk = dir.mkpath(m_databaseDirectory);
        if (!createOk) {
            qWarning(auxdb) << "Unable to create DB directory" << m_databaseDirectory;
            return;
        }
    };
    m_avatarMapTable = new AvatarMapTable(this, this);

    // Open the database.
    if (!openDB())
        return;

    QSqlQuery query(*m_db);
    // Turn synchronous off.
    if (!query.exec("PRAGMA synchronous = OFF")) {
        logSqlError(query);
        return;
    }

    // Enable foreign keys.
    if (!query.exec("PRAGMA foreign_keys = ON")) {
        logSqlError(query);
        return;
    }

    // Update if needed.
    upgradeSchema(schemaVersion());
}

/*!
 * \brief Database::~Database
 */
AuxDatabase::~AuxDatabase()
{
    delete m_avatarMapTable;
}

/*!
 * \brief Database::logSqlError Logs a SQL error
 * \param q
 */
void AuxDatabase::logSqlError(QSqlQuery &q) const
{
    qDebug(auxdb) << "SQLite error: " << q.lastError();
    qDebug(auxdb) << "SQLite string: " << q.lastQuery();
}

/*!
 * \brief Database::openDB Open the SQLite database
 * \return
 */
bool AuxDatabase::openDB()
{
    *m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db->setDatabaseName(getDBname());
    if (!m_db->open()) {
        qDebug(auxdb) << "Error opening DB: " << m_db->lastError().text();
        return false;
    }

    return true;
}

/*!
 * \brief Database::schemaVersion Get schema version
 * \return
 */
int AuxDatabase::schemaVersion() const
{
    QSqlQuery query(*m_db);
    if (!query.exec("PRAGMA user_version") || !query.next()) {
        logSqlError(query);
        return -1;
    }

    return query.value(0).toInt();
}

/*!
 * \brief Database::setSchemaVersion Set schema version
 * \param version
 */
void AuxDatabase::setSchemaVersion(int version)
{
    // Must use string concats here since prepared statements
    // appear not to work with PRAGMAs.
    QSqlQuery query(*m_db);
    if (!query.exec("PRAGMA user_version = " + QString::number(version)))
        logSqlError(query);
}

/*!
 * \brief Database::upgradeSchema Upgrades the schema from current_version to
 * the latest & greatest
 * FIXME this should upgrade the whole DB (every row of every table)
 * \param current_version
 */
void AuxDatabase::upgradeSchema(int current_version)
{
    qWarning(auxdb) << "Schema migration, current version" << current_version;
    int version = current_version + 1;
    for (;; version++) {
        // Check for the existence of an updated db file.
        // Filename format is n.sql, where n is the schema version number.
        QFile file(getSqlDir() + QDir::separator() + QString::number(version) + ".sql");
        qWarning(auxdb) << "Trying to execute the following migration file:" << file.fileName();
        if (!file.exists())
            return;

        if (!executeSqlFile(file))
            return;

        // Update version.
        setSchemaVersion(version);
    }
    qWarning(auxdb) << "Schemaversion set to" << version - 1;
}

/*!
 * \brief Database::executeSqlFile Executes a text file containing SQL commands
 * \param file
 * \return
 */
bool AuxDatabase::executeSqlFile(QFile &file)
{
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug(auxdb) << "Could not open file: " << file.fileName();
        return false;
    }

    // Read entire file into a string.
    QString sql;
    QTextStream in(&file);
    while (!in.atEnd())
        sql += in.readLine() + "\n";
    file.close();

    // Split string at semi-colons to break into multiple statements.
    // This is due to the SQLite driver's inability to handle multiple
    // statements in a single string.
    QStringList statements = sql.split(";", QString::SkipEmptyParts);
    foreach (QString statement, statements) {
        if (statement.trimmed() == "")
            continue;

        // Execute each statement.
        QSqlQuery query(*m_db);
        if (!query.exec(statement)) {
            qDebug(auxdb) << "Error executing database file: " << file.fileName();
            logSqlError(query);
        }
    }

    return true;
}

/*!
 * \brief Database::getAvatarMapTable
 * \return
 */
AvatarMapTable *AuxDatabase::getAvatarMapTable() const
{
    return m_avatarMapTable;
}

/*!
 * \brief Database::getDB
 * \return
 */
QSqlDatabase *AuxDatabase::getDB()
{
    return m_db;
}

/*!
 * \brief Database::getSqlDir Returns the directory where the .sql files live
 * \return
 */
const QString &AuxDatabase::getSqlDir() const
{
    return m_sqlSchemaDirectory;
}

/*!
* \brief get_db_name
* \return the filename of the database
*/
QString AuxDatabase::getDBname() const
{
    return m_databaseDirectory + "/auxdb.sqlite";
}
