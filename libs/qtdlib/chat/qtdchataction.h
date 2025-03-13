#ifndef QTDCHATACTION_H
#define QTDCHATACTION_H

#include <QObject>
#include "common/qabstracttdobject.h"

class QTdChatAction : public QTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString personal_description READ personal_description)
    Q_PROPERTY(QString singular_description READ singular_description)
    Q_PROPERTY(QString plural_description READ plural_description)
    Q_DISABLE_COPY(QTdChatAction)
public:
    explicit QTdChatAction(QObject *parent = nullptr);

    QString personal_description();
    QString singular_description();
    QString plural_description();

protected:
    QString m_personal_description;
    QString m_singular_description;
    QString m_plural_description;
};

class QTdChatActionCancel : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionCancel)
public:
    explicit QTdChatActionCancel(QObject *parent = nullptr);
};

class QTdChatActionChoosingContact : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionChoosingContact)
public:
    explicit QTdChatActionChoosingContact(QObject *parent = nullptr);
};

class QTdChatActionChoosingLocation : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionChoosingLocation)
public:
    explicit QTdChatActionChoosingLocation(QObject *parent = nullptr);
};

class QTdChatActionRecordingVideo : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionRecordingVideo)
public:
    explicit QTdChatActionRecordingVideo(QObject *parent = nullptr);
};

class QTdChatActionRecordingVideoNote : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionRecordingVideoNote)
public:
    explicit QTdChatActionRecordingVideoNote(QObject *parent = nullptr);
};

class QTdChatActionRecordingVoiceNote : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionRecordingVoiceNote)
public:
    explicit QTdChatActionRecordingVoiceNote(QObject *parent = nullptr);
};

class QTdChatActionStartPlayingGame : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionStartPlayingGame)
public:
    explicit QTdChatActionStartPlayingGame(QObject *parent = nullptr);
};

class QTdChatActionTyping : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionTyping)
public:
    explicit QTdChatActionTyping(QObject *parent = nullptr);
};

class QTdChatActionUploadingDocument : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionUploadingDocument)
public:
    explicit QTdChatActionUploadingDocument(QObject *parent = nullptr);
};

class QTdChatActionUploadingPhoto : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionUploadingPhoto)
public:
    explicit QTdChatActionUploadingPhoto(QObject *parent = nullptr);
};

class QTdChatActionUploadingVideo : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionUploadingVideo)
public:
    explicit QTdChatActionUploadingVideo(QObject *parent = nullptr);
};

class QTdChatActionUploadingVideoNote : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionUploadingVideoNote)
public:
    explicit QTdChatActionUploadingVideoNote(QObject *parent = nullptr);
};

class QTdChatActionUploadingVoiceNote : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionUploadingVoiceNote)
public:
    explicit QTdChatActionUploadingVoiceNote(QObject *parent = nullptr);
};

class QTdChatActionChoosingSticker : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionChoosingSticker)
public:
    explicit QTdChatActionChoosingSticker(QObject *parent = nullptr);
};

class QTdChatActionRecordingAudio : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionRecordingAudio)
public:
    explicit QTdChatActionRecordingAudio(QObject *parent = nullptr);
};

class QTdChatActionUploadingAudio : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionUploadingAudio)
public:
    explicit QTdChatActionUploadingAudio(QObject *parent = nullptr);
};

class QTdChatActionUnknown : public QTdChatAction
{
    Q_OBJECT
    Q_DISABLE_COPY(QTdChatActionUnknown)
public:
    explicit QTdChatActionUnknown(QObject *parent = nullptr);
};

#endif // QTDCHATACTION_H
