#include "qtdchatactionfactory.h"
#include <QDebug>

QTdChatAction *QTdChatActionFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    if (type == "chatActionCancel") {
        return new QTdChatActionCancel(parent);
    } else if (type == "chatActionChoosingContact") {
        return new QTdChatActionChoosingContact(parent);
    } else if (type == "chatActionChoosingLocation") {
        return new QTdChatActionChoosingLocation(parent);
    } else if (type == "chatActionRecordingAudio") {
        return new QTdChatActionRecordingAudio(parent);
    } else if (type == "chatActionRecordingVideo") {
        return new QTdChatActionRecordingVideo(parent);
    } else if (type == "chatActionRecordingVideoNote") {
        return new QTdChatActionRecordingVideoNote(parent);
    } else if (type == "chatActionRecordingVoiceNote") {
        return new QTdChatActionRecordingVoiceNote(parent);
    } else if (type == "chatActionStartPlayingGame") {
        return new QTdChatActionStartPlayingGame(parent);
    } else if (type == "chatActionTyping") {
        return new QTdChatActionTyping(parent);
    } else if (type == "chatActionUploadingAudio") {
        return new QTdChatActionUploadingAudio(parent);
    } else if (type == "chatActionUploadingDocument") {
        return new QTdChatActionUploadingDocument(parent);
    } else if (type == "chatActionUploadingPhoto") {
        return new QTdChatActionUploadingPhoto(parent);
    } else if (type == "chatActionUploadingVideo") {
        return new QTdChatActionUploadingVideo(parent);
    } else if (type == "chatActionUploadingVideoNote") {
        return new QTdChatActionUploadingVideoNote(parent);
    } else if (type == "chatActionUploadingVoiceNote") {
        return new QTdChatActionUploadingVoiceNote(parent);
    } else if (type == "chatActionChoosingSticker") {
        return new QTdChatActionChoosingSticker(parent);
    }
    qWarning() << "Received unknown chat action" << type;
    return new QTdChatActionUnknown(parent);
}
