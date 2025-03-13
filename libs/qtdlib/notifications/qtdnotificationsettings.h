#ifndef QTDNOTIFICATIONSETTINGS_H
#define QTDNOTIFICATIONSETTINGS_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdNotificationSettings : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(bool useDefaultMuteFor READ useDefaultMuteFor NOTIFY muteForChanged)
    Q_PROPERTY(qint32 muteFor READ muteFor WRITE setMuteFor NOTIFY muteForChanged)
    Q_PROPERTY(bool useDefaultSound READ useDefaultSound NOTIFY soundChanged)
    Q_PROPERTY(QString sound READ sound NOTIFY soundChanged)
    Q_PROPERTY(bool useDefaultShowPreview READ useDefaultShowPreview NOTIFY showPreviewChanged)
    Q_PROPERTY(bool showPreview READ showPreview NOTIFY showPreviewChanged)
    Q_PROPERTY(bool useDefaultDisablePinnedMsgNotes READ useDefaultDisablePinnedMsgNotes NOTIFY disablePinnedMsgNotesChanged)
    Q_PROPERTY(bool disablePinnedMsgNotes READ disablePinnedMsgNotes NOTIFY disablePinnedMsgNotesChanged)
    Q_PROPERTY(bool useDefaultDisableMentionNotes READ useDefaultDisableMentionNotes NOTIFY disableMentionNotesChanged)
    Q_PROPERTY(bool disableMentionNotes READ disableMentionNotes NOTIFY disableMentionNotesChanged)

public:
    explicit QTdNotificationSettings(QObject *parent = nullptr);


    bool useDefaultMuteFor() const;
    void setUseDefaultMuteFor(const bool &value);
    qint32 muteFor() const;
    void setMuteFor(const qint32 &duration);
    bool useDefaultSound() const;
    QString sound() const;
    bool useDefaultShowPreview() const;
    bool showPreview() const;
    bool useDefaultDisablePinnedMsgNotes() const;
    bool disablePinnedMsgNotes() const;
    bool useDefaultDisableMentionNotes() const;
    bool disableMentionNotes() const;

    void unmarshalJson(const QJsonObject &json) override;
    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();
    
signals:
    void muteForChanged();
    void soundChanged();
    void showPreviewChanged();
    void disablePinnedMsgNotesChanged();
    void disableMentionNotesChanged();

private:
    Q_DISABLE_COPY(QTdNotificationSettings)
    bool m_useDefaultMuteFor;
    qint32 m_muteFor;
    bool m_useDefaultSound;
    QString m_sound;
    bool m_useDefaultShowPreview;
    bool m_showPreview;
    bool m_useDefaultDisablePinnedMsgNotes;
    bool m_disablePinnedMsgNotes;
    bool m_useDefaultDisableMentionNotes;
    bool m_disableMentionNotes;
};

#endif // QTDNOTIFICATIONSETTINGS_H
