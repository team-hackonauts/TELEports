/*
 * Copyright (C) 2024 UBPorts Foundation
 *
 * WARNING: This is a generated file. Do not modify directly.
 * Any changes made to this file will be overwritten.
 * 
 * Generated on: 2024-07-26
 * Generated by: TELEports tlparser.py
 * 
 * For any modifications, please edit the source templates and regenerate this file.
 */

#include "qtdchatpermissions.h"

#include <QJsonObject>
#include <QJsonArray>

QTdChatPermissions::QTdChatPermissions(QObject *parent)
    : QTdObject(parent)
{
}

QTdChatPermissions::QTdChatPermissions(QObject *parent, bool canSendMessages_, bool canSendAudios_, bool canSendDocuments_, bool canSendPhotos_, bool canSendVideos_, bool canSendVideoNotes_, bool canSendVoiceNotes_, bool canSendPolls_, bool canSendOtherMessages_, bool canAddWebPagePreviews_, bool canChangeInfo_, bool canInviteUsers_, bool canPinMessages_, bool canManageTopics_)
    : QTdObject(parent),
    m_canSendMessages(canSendMessages_),
    m_canSendAudios(canSendAudios_),
    m_canSendDocuments(canSendDocuments_),
    m_canSendPhotos(canSendPhotos_),
    m_canSendVideos(canSendVideos_),
    m_canSendVideoNotes(canSendVideoNotes_),
    m_canSendVoiceNotes(canSendVoiceNotes_),
    m_canSendPolls(canSendPolls_),
    m_canSendOtherMessages(canSendOtherMessages_),
    m_canAddWebPagePreviews(canAddWebPagePreviews_),
    m_canChangeInfo(canChangeInfo_),
    m_canInviteUsers(canInviteUsers_),
    m_canPinMessages(canPinMessages_),
    m_canManageTopics(canManageTopics_) {
}

bool QTdChatPermissions::canSendMessages() const {
    return m_canSendMessages;
}

void QTdChatPermissions::setCanSendMessages(bool value) {
    if (m_canSendMessages != value) {
        m_canSendMessages = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canSendAudios() const {
    return m_canSendAudios;
}

void QTdChatPermissions::setCanSendAudios(bool value) {
    if (m_canSendAudios != value) {
        m_canSendAudios = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canSendDocuments() const {
    return m_canSendDocuments;
}

void QTdChatPermissions::setCanSendDocuments(bool value) {
    if (m_canSendDocuments != value) {
        m_canSendDocuments = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canSendPhotos() const {
    return m_canSendPhotos;
}

void QTdChatPermissions::setCanSendPhotos(bool value) {
    if (m_canSendPhotos != value) {
        m_canSendPhotos = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canSendVideos() const {
    return m_canSendVideos;
}

void QTdChatPermissions::setCanSendVideos(bool value) {
    if (m_canSendVideos != value) {
        m_canSendVideos = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canSendVideoNotes() const {
    return m_canSendVideoNotes;
}

void QTdChatPermissions::setCanSendVideoNotes(bool value) {
    if (m_canSendVideoNotes != value) {
        m_canSendVideoNotes = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canSendVoiceNotes() const {
    return m_canSendVoiceNotes;
}

void QTdChatPermissions::setCanSendVoiceNotes(bool value) {
    if (m_canSendVoiceNotes != value) {
        m_canSendVoiceNotes = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canSendPolls() const {
    return m_canSendPolls;
}

void QTdChatPermissions::setCanSendPolls(bool value) {
    if (m_canSendPolls != value) {
        m_canSendPolls = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canSendOtherMessages() const {
    return m_canSendOtherMessages;
}

void QTdChatPermissions::setCanSendOtherMessages(bool value) {
    if (m_canSendOtherMessages != value) {
        m_canSendOtherMessages = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canAddWebPagePreviews() const {
    return m_canAddWebPagePreviews;
}

void QTdChatPermissions::setCanAddWebPagePreviews(bool value) {
    if (m_canAddWebPagePreviews != value) {
        m_canAddWebPagePreviews = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canChangeInfo() const {
    return m_canChangeInfo;
}

void QTdChatPermissions::setCanChangeInfo(bool value) {
    if (m_canChangeInfo != value) {
        m_canChangeInfo = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canInviteUsers() const {
    return m_canInviteUsers;
}

void QTdChatPermissions::setCanInviteUsers(bool value) {
    if (m_canInviteUsers != value) {
        m_canInviteUsers = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canPinMessages() const {
    return m_canPinMessages;
}

void QTdChatPermissions::setCanPinMessages(bool value) {
    if (m_canPinMessages != value) {
        m_canPinMessages = value;
        emit dataChanged();
    }
}

bool QTdChatPermissions::canManageTopics() const {
    return m_canManageTopics;
}

void QTdChatPermissions::setCanManageTopics(bool value) {
    if (m_canManageTopics != value) {
        m_canManageTopics = value;
        emit dataChanged();
    }
}

QJsonObject QTdChatPermissions::marshalJson() {
    return QJsonObject{
        { "@type", QTdObject::typeString() },
        { "can_send_messages", m_canSendMessages },
        { "can_send_audios", m_canSendAudios },
        { "can_send_documents", m_canSendDocuments },
        { "can_send_photos", m_canSendPhotos },
        { "can_send_videos", m_canSendVideos },
        { "can_send_video_notes", m_canSendVideoNotes },
        { "can_send_voice_notes", m_canSendVoiceNotes },
        { "can_send_polls", m_canSendPolls },
        { "can_send_other_messages", m_canSendOtherMessages },
        { "can_add_web_page_previews", m_canAddWebPagePreviews },
        { "can_change_info", m_canChangeInfo },
        { "can_invite_users", m_canInviteUsers },
        { "can_pin_messages", m_canPinMessages },
        { "can_manage_topics", m_canManageTopics }
    };
}

void QTdChatPermissions::unmarshalJson(const QJsonObject &json) {
    QJsonObject jsonObj;
    QJsonArray jsonArray;

    QTdObject::unmarshalJson(json);
    m_canSendMessages = json["can_send_messages"].toBool();
    m_canSendAudios = json["can_send_audios"].toBool();
    m_canSendDocuments = json["can_send_documents"].toBool();
    m_canSendPhotos = json["can_send_photos"].toBool();
    m_canSendVideos = json["can_send_videos"].toBool();
    m_canSendVideoNotes = json["can_send_video_notes"].toBool();
    m_canSendVoiceNotes = json["can_send_voice_notes"].toBool();
    m_canSendPolls = json["can_send_polls"].toBool();
    m_canSendOtherMessages = json["can_send_other_messages"].toBool();
    m_canAddWebPagePreviews = json["can_add_web_page_previews"].toBool();
    m_canChangeInfo = json["can_change_info"].toBool();
    m_canInviteUsers = json["can_invite_users"].toBool();
    m_canPinMessages = json["can_pin_messages"].toBool();
    m_canManageTopics = json["can_manage_topics"].toBool();

    emit dataChanged();
}

