#include "messagedelegatemap.h"
#include <common/qabstracttdobject.h>

MessageDelegateMap::MessageDelegateMap(QObject *parent)
    : QObject(parent)
{
    m_delegates.insert(QTdObject::MESSAGE_ACTION, QStringLiteral("qrc:///delegates/MessageActionItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_ANIMATION, QStringLiteral("qrc:///delegates/MessageAnimationItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_UNREAD_LABEL, QStringLiteral("qrc:///delegates/MessageUnreadLabelItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_AUDIO, QStringLiteral("qrc:///delegates/MessageAudioItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_BASIC_GROUP_CHAT_CREATE, QStringLiteral("qrc:///delegates/MessageBasicGroupChatCreate.qml"));
    m_delegates.insert(QTdObject::MESSAGE_SUPER_GROUP_CHAT_CREATE, QStringLiteral("qrc:///delegates/MessageBasicGroupChatCreate.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CALL, QStringLiteral("qrc:///delegates/MessageCallItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CHAT_ADD_MEMBERS, QStringLiteral("qrc:///delegates/MessageChatAddMembersItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CHAT_CHANGE_PHOTO, QStringLiteral("qrc:///delegates/MessageChatChangePhoto.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CHAT_CHANGE_TITLE, QStringLiteral("qrc:///delegates/MessageChatChangeTitle.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CHAT_DELETE_MEMBER, QStringLiteral("qrc:///delegates/MessageChatDeleteMember.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CHAT_DELETE_PHOTO, QStringLiteral("qrc:///delegates/MessageChatDeletePhoto.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CHAT_JOIN_BY_LINK, QStringLiteral("qrc:///delegates/MessageJoinByLink.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CHAT_SET_MESSAGE_AUTO_DELETE_TIME, QStringLiteral("qrc:///delegates/MessageChatSetMessageAutodeleteTime.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CHAT_UPGRADE_FROM, QStringLiteral("qrc:///delegates/MessageChatUpgradeFrom.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CHAT_UPGRADE_TO, QStringLiteral("qrc:///delegates/MessageChatUpgradeTo.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CUSTOM_SERVICE_ACTION, QStringLiteral("qrc:///delegates/MessageCustomServiceAction.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CONTACT_REGISTERED, QStringLiteral("qrc:///delegates/MessageContactRegistered.qml"));
    m_delegates.insert(QTdObject::MESSAGE_CONTACT, QStringLiteral("qrc:///delegates/MessageContactItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_DATE, QStringLiteral("qrc:///delegates/MessageDateItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_DOCUMENT, QStringLiteral("qrc:///delegates/MessageDocumentItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_HIDDEN, QStringLiteral("qrc:///delegates/MessageHiddenItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_LOCATION, QStringLiteral("qrc:///delegates/MessageLocationItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_PIN_MESSAGE, QStringLiteral("qrc:///delegates/MessagePinMessage.qml"));
    m_delegates.insert(QTdObject::MESSAGE_SCREENSHOT_TAKEN, QStringLiteral("qrc:///delegates/MessageScreenshotTaken.qml"));
    m_delegates.insert(QTdObject::MESSAGE_TEXT, QStringLiteral("qrc:///delegates/MessageTextItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_PHOTO, QStringLiteral("qrc:///delegates/MessagePhotoItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_POLL, QStringLiteral("qrc:///delegates/MessagePollItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_STICKER, QStringLiteral("qrc:///delegates/MessageStickerItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_VIDEO, QStringLiteral("qrc:///delegates/MessageVideoItem.qml"));
    m_delegates.insert(QTdObject::MESSAGE_VIDEO_NOTE, QStringLiteral("qrc:///delegates/MessageVideoNote.qml"));
    m_delegates.insert(QTdObject::MESSAGE_VOICE_NOTE, QStringLiteral("qrc:///delegates/MessageVoiceNote.qml"));
    m_delegates.insert(QTdObject::MESSAGE_UNSUPPORTED, QStringLiteral("qrc:///delegates/MessageUnsupported.qml"));

    m_default = QStringLiteral("qrc:///delegates/NotImplementedYet.qml");
}

QString MessageDelegateMap::findComponent(const int &type)
{
    return m_delegates.value(type, m_default);
}
