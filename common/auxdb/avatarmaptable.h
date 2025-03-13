#ifndef AVATARMAP_H
#define AVATARMAP_H

#include <QList>
#include <QObject>

class AuxDatabase;

class AvatarMapTable : public QObject
{
    Q_OBJECT

public:
    explicit AvatarMapTable(AuxDatabase *db, QObject *parent = 0);

    QString getAvatarPathbyId(const qint64 id);
    void setMapEntry(const qint64 id, const QString path);
    void setUnreadMapEntry(const qint64 id, const qint32 unread_count);
    void removeMapEntry(const qint64 id);
    void resetUnreadMap();
    qint32 getTotalUnread();

private:
    AuxDatabase *m_db;
};

#endif // AVATARMAP_H
