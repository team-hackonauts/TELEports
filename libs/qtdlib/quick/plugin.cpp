#include <QtQml>
#include <QtQml/QQmlContext>

#include "plugin.h"
#include "auth/qtdauthmanager.h"
#include "connections/qtdconnectionmanager.h"
#include "users.h"
#include "contacts.h"

#include "auth/qtdauthstate.h"
#include "call/qtdcalldiscardreason.h"
#include "chat/qtdchat.h"
#include "chat/requests/qtdchatreportreason.h"
#include "chat/qtdchatlistmodel.h"
#include "chat/qtdchatlistsortfiltermodel.h"
#include "connections/qtdconnectionstate.h"
#include "user/qtduser.h"
#include "files/qtdfile.h"
#include "files/qtdanimation.h"
#include "files/qtdphotosize.h"
#include "files/qtdaudio.h"
#include "files/qtdvideo.h"
#include "files/qtddocument.h"
#include "files/qtdsticker.h"
#include "files/qtdthumbnail.h"
#include "files/qtdminithumbnail.h"
#include "messages/qtdmessage.h"
#include "messages/qtdmessagelistmodel.h"
#include "messages/qtdmessagecontent.h"
#include "messages/qtdchatstate.h"
#include "messages/content/qtdmessageanimation.h"
#include "messages/content/qtdmessageaudio.h"
#include "messages/content/qtdmessagebasicgroupchatcreate.h"
#include "messages/content/qtdmessagecall.h"
#include "messages/content/qtdmessagechataddmembers.h"
#include "messages/content/qtdmessagechatchangephoto.h"
#include "messages/content/qtdmessagechatchangetitle.h"
#include "messages/content/qtdmessagechatdeletemember.h"
#include "messages/content/qtdmessagechatdeletephoto.h"
#include "messages/content/qtdmessagechatjoinbylink.h"
#include "messages/content/qtdmessagechatsetmessageautodeletetime.h"
#include "messages/content/qtdmessagechatupgradefrom.h"
#include "messages/content/qtdmessagechatupgradeto.h"
#include "messages/content/qtdmessagedocument.h"
#include "messages/content/qtdmessagelocation.h"
#include "messages/content/qtdmessagephoto.h"
#include "messages/content/qtdmessagepoll.h"
#include "messages/content/qtdmessagesticker.h"
#include "messages/content/qtdmessagescreenshottaken.h"
#include "messages/content/qtdmessagetext.h"
#include "messages/content/qtdmessagevideo.h"
#include "messages/content/qtdmessagevideonote.h"
#include "messages/content/qtdmessagevoicenote.h"
#include "messages/content/qtdmessagecontact.h"
#include "messages/content/qtdmessageunsupported.h"
#include "notifications/qtdenablenotifications.h"
#include "settings/qtdsettings.h"
#include "stickers/qtdstickersets.h"

#include "utils/qtdtextformatter.h"

void QTdLib::registerQmlTypes()
{
    static bool registered = false;
    if (registered) {
        return;
    }
    registered = true;

    static const char *uri = "QTelegram";
    //@uri QTelegram
    qmlRegisterType<QTdSettings>(uri, 1, 0, "Settings");
    qmlRegisterType<QTdAuthManager>(uri, 1, 0, "AuthState");
    // ConnectionManager singleton
    qmlRegisterSingletonType<QTdConnectionManager>(uri, 1, 0, "ConnectionManager", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        QTdConnectionManager *connectionManager = new QTdConnectionManager();
        return connectionManager;
    });
    qmlRegisterType<QTdAuthParams>(uri, 1, 0, "AuthParams");
    qmlRegisterType<Users>(uri, 1, 0, "Users");
    qmlRegisterType<Contacts>(uri, 1, 0, "Contacts");
    qmlRegisterType<QTdChatListModel>(uri, 1, 0, "ChatList");
    qmlRegisterType<QTdChatListSortFilterModel>(uri, 1, 0, "SortedChatList");
    qmlRegisterType<QTdMessageListModel>(uri, 1, 0, "MessageList");

    qmlRegisterUncreatableType<QTdChatState>(uri, 1, 0, "ChatState", "Enum type is uncreatable");

    qmlRegisterType<QTdTextFormatter>(uri, 1, 0, "TextFormatter");
    qmlRegisterType<QTdEnableNotifications>(uri, 1, 0, "EnableNotifications");

    qmlRegisterType<QTdStickerSets>(uri, 1, 0, "StickerSets");

    // qtdlib call
    qmlRegisterUncreatableType<QTdCallDiscardReason>(uri, 1, 0, "QTdCallDiscardReason", "c++ class");
    qmlRegisterUncreatableType<QTdCallDiscardReasonDeclined>(uri, 1, 0, "QTdCallDiscardReasonDeclined", "c++ class");
    qmlRegisterUncreatableType<QTdCallDiscardReasonDisconnected>(uri, 1, 0, "QTdCallDiscardReasonDisconnected", "c++ class");
    qmlRegisterUncreatableType<QTdCallDiscardReasonEmpty>(uri, 1, 0, "QTdCallDiscardReasonEmpty", "c++ class");
    qmlRegisterUncreatableType<QTdCallDiscardReasonHungUp>(uri, 1, 0, "QTdCallDiscardReasonHungUp", "c++ class");
    qmlRegisterUncreatableType<QTdCallDiscardReasonMissed>(uri, 1, 0, "QTdCallDiscardReasonMissed", "c++ class");

    // qtdlib common
    qmlRegisterUncreatableType<QTdObject>(uri, 1, 0, "QTdObject", "Base TD c++ class");
    qmlRegisterType<QTdMediaSizeExtractor>(uri, 1, 0, "QTdMediaSizeExtractor");

    // qtdlib chat
    qmlRegisterUncreatableType<QTdChat>(uri, 1, 0, "QTdChat", "c++ class");
    qmlRegisterUncreatableType<QTdChatType>(uri, 1, 0, "QTdChatType", "abstract c++ class");
    qmlRegisterUncreatableType<QTdChatTypeBasicGroup>(uri, 1, 0, "QTdChatTypeBasicGroup", "c++ class");
    qmlRegisterUncreatableType<QTdChatTypePrivate>(uri, 1, 0, "QTdChatTypePrivate", "c++ class");
    qmlRegisterUncreatableType<QTdChatTypeSecret>(uri, 1, 0, "QTdChatTypeSecret", "c++ class");
    qmlRegisterUncreatableType<QTdChatTypeSuperGroup>(uri, 1, 0, "QTdChatTypeSuperGroup", "c++ class");
    qmlRegisterUncreatableType<QTdChatPhoto>(uri, 1, 0, "QTdChatPhoto", "c++ class");
    qmlRegisterUncreatableType<QTdChatReportReason>(uri, 1, 0, "QTdChatReportReason", "c++ class");
    qRegisterMetaType<QTdChatReportReason::ChatReportReasonType>("ChatReportReasonType");

    // qtdlib auth
    qmlRegisterUncreatableType<QTdAuthState>(uri, 1, 0, "QTdAuthState", "Base TD auth state class");
    qmlRegisterUncreatableType<QTdAuthStateWaitParams>(uri, 1, 0, "QTdAuthStateWaitParams", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateWaitEncryptionKey>(uri, 1, 0, "QTdAuthStateWaitEncryptionKey", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateWaitPhoneNumber>(uri, 1, 0, "QTdAuthStateWaitPhoneNumber", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateWaitCode>(uri, 1, 0, "QTdAuthStateWaitCode", "c++ class");
    qmlRegisterUncreatableType<QTdAuthCodeInfo>(uri, 1, 0, "QTdAuthCodeInfo", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateWaitPassword>(uri, 1, 0, "QTdAuthStateWaitPassword", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateReady>(uri, 1, 0, "QTdAuthStateReady", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateLoggingOut>(uri, 1, 0, "QTdAuthStateLoggingOut", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateClosing>(uri, 1, 0, "QTdAuthStateClosing", "c++ class");
    qmlRegisterUncreatableType<QTdAuthStateClosed>(uri, 1, 0, "QTdAuthStateClosed", "c++ class");
    qmlRegisterUncreatableType<QTdAuthCodeTelegramMessage>(uri, 1, 0, "QTdAuthCodeTelegramMessage", "c++ class");
    qmlRegisterUncreatableType<QTdAuthCodeSms>(uri, 1, 0, "QTdAuthCodeSms", "c++ class");
    qmlRegisterUncreatableType<QTdAuthCodeCall>(uri, 1, 0, "QTdAuthCodeCall", "c++ class");
    qmlRegisterUncreatableType<QTdAuthCodeFlashCall>(uri, 1, 0, "QTdAuthCodeFlashCall", "c++ class");


    // qtdlib connections
    qmlRegisterUncreatableType<QTdConnectionState>(uri, 1, 0, "QTdConnectionState", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateWaitingForNetwork>(uri, 1, 0, "QTdConnectionStateWaitingForNetwork", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateConnectingToProxy>(uri, 1, 0, "QTdConnectionStateConnectingToProxy", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateConnecting>(uri, 1, 0, "QTdConnectionStateConnecting", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateUpdating>(uri, 1, 0, "QTdConnectionStateUpdating", "c++ class");
    qmlRegisterUncreatableType<QTdConnectionStateReady>(uri, 1, 0, "QTdConnectionStateReady", "c++ class");

    // qtdlib users
    qmlRegisterUncreatableType<QTdUser>(uri, 1, 0, "QTdUser", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatus>(uri, 1, 0, "QTdUserStatus", "Abstract status type");
    qmlRegisterUncreatableType<QTdUserStatusEmpty>(uri, 1, 0, "QTdUserStatusEmpty", "c++ class");
    qmlRegisterUncreatableType<QTdUserStateLastMonth>(uri, 1, 0, "QTdUserStateLastMonth", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatusLastWeek>(uri, 1, 0, "QTdUserStatusLastWeek", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatusOffline>(uri, 1, 0, "QTdUserStatusOffline", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatusOnline>(uri, 1, 0, "QTdUserStatusOnline", "c++ class");
    qmlRegisterUncreatableType<QTdUserStatusRecently>(uri, 1, 0, "QTdUserStatusRecently", "c++ class");
    qmlRegisterUncreatableType<QTdProfilePhoto>(uri, 1, 0, "QTdProfilePhoto", "c++ class");
    qmlRegisterUncreatableType<QTdUserType>(uri, 1, 0, "QTdUserType", "Abstract class");
    qmlRegisterUncreatableType<QTdUserTypeBot>(uri, 1, 0, "QTdUserTypeBot", "c++ class");
    qmlRegisterUncreatableType<QTdUserTypeDeleted>(uri, 1, 0, "QTdUserTypeDeleted", "c++ class");
    qmlRegisterUncreatableType<QTdUserTypeRegular>(uri, 1, 0, "QTdUserTypeRegular", "c++ class");
    qmlRegisterUncreatableType<QTdUserTypeUnknown>(uri, 1, 0, "QTdUserTypeUnknown", "c++ class");

    // qtdlib files
    qmlRegisterUncreatableType<QTdFile>(uri, 1, 0, "QTdFile", "c++ class");
    qmlRegisterUncreatableType<QTdLocalFile>(uri, 1, 0, "QTdLocalFile", "c++ class");
    qmlRegisterUncreatableType<QTdRemoteFile>(uri, 1, 0, "QTdRemoteFile", "c++ class");
    qmlRegisterUncreatableType<QTdAnimation>(uri, 1, 0, "QTdAnimation", "c++ class");
    qmlRegisterUncreatableType<QTdPhoto>(uri, 1, 0, "QTdPhoto", "c++ class");
    qmlRegisterUncreatableType<QTdPhotoSize>(uri, 1, 0, "QTdPhotoSize", "c++ class");
    qmlRegisterUncreatableType<QTdThumbnail>(uri, 1, 0, "QTdThumbnail", "c++ class");
    qmlRegisterUncreatableType<QTdMiniThumbnail>(uri, 1, 0, "QTdMiniThumbnail", "c++ class");
    qmlRegisterUncreatableType<QTdAudio>(uri, 1, 0, "QTdAudio", "c++ class");
    qmlRegisterUncreatableType<QTdVideo>(uri, 1, 0, "QTdVideo", "c++ class");
    qmlRegisterUncreatableType<QTdDocument>(uri, 1, 0, "QTdDocument", "c++ class");
    qmlRegisterUncreatableType<QTdSticker>(uri, 1, 0, "QTdSticker", "c++ class");

    // qtdlib notifications
    qmlRegisterUncreatableType<QTdNotificationSettings>(uri, 1, 0, "QTdNotificationSettings", "C++ class");

    // qtdlib messages
    qmlRegisterUncreatableType<QTdMessage>(uri, 1, 0, "QTdMessage", "C++ class");
    // message content types
    qmlRegisterUncreatableType<QTdMessageContent>(uri, 1, 0, "QTdMessageContent", "C++ class");
    qmlRegisterUncreatableType<QTdMessageAnimation>(uri, 1, 0, "QTdMessageAnimation", "C++ class");
    qmlRegisterUncreatableType<QTdMessageAudio>(uri, 1, 0, "QTdMessageAudio", "C++ class");
    qmlRegisterUncreatableType<QTdMessageBasicGroupChatCreate>(uri, 1, 0, "QTdMessageBasicGroupChatCreate", "C++ class");
    qmlRegisterUncreatableType<QTdMessageCall>(uri, 1, 0, "QTdMessageCall", "C++ class");
    qmlRegisterUncreatableType<QTdMessageChatAddMembers>(uri, 1, 0, "QTdMessageChatAddMembers", "C++ class");
    qmlRegisterUncreatableType<QTdMessageChatChangePhoto>(uri, 1, 0, "QTdMessageChatChangePhoto", "C++ class");
    qmlRegisterUncreatableType<QTdMessageChatChangeTitle>(uri, 1, 0, "QTdMessageChatChangeTitle", "C++ class");
    qmlRegisterUncreatableType<QTdMessageChatDeleteMember>(uri, 1, 0, "QTdMessageChatDeleteMember", "C++ class");
    qmlRegisterUncreatableType<QTdMessageChatDeletePhoto>(uri, 1, 0, "QTdMessageChatDeletePhoto", "C++ class");
    qmlRegisterUncreatableType<QTdMessageChatJoinByLink>(uri, 1, 0, "QTdMessageChatJoinByLink", "C++ class");
    qmlRegisterUncreatableType<QTdMessageChatSetMessageAutoDeleteTime>(uri, 1, 0, "QTdMessageChatSetMessageAutoDeleteTime", "C++ class");
    qmlRegisterUncreatableType<QTdMessageChatUpgradeFrom>(uri, 1, 0, "QTdMessageChatUpgradeFrom", "C++ class");
    qmlRegisterUncreatableType<QTdMessageChatUpgradeTo>(uri, 1, 0, "QTdMessageChatUpgradeTo", "C++ class");
    qmlRegisterUncreatableType<QTdMessageDocument>(uri, 1, 0, "QTdMessageDocument", "C++ class");
    qmlRegisterUncreatableType<QTdMessageLocation>(uri, 1, 0, "QTdMessageLocation", "C++ class");
    qmlRegisterUncreatableType<QTdMessageHidden>(uri, 1, 0, "QTdMessageHidden", "C++ class");
    qmlRegisterUncreatableType<QTdMessagePhoto>(uri, 1, 0, "QTdMessagePhoto", "C++ class");
    qmlRegisterUncreatableType<QTdMessagePoll>(uri, 1, 0, "QTdMessagePoll", "C++ class");
    qmlRegisterUncreatableType<QTdMessageSticker>(uri, 1, 0, "QTdMessageSticker", "C++ class");
    qmlRegisterUncreatableType<QTdMessageText>(uri, 1, 0, "QTdMessageText", "C++ class");
    qmlRegisterUncreatableType<QTdMessageScreenshotTaken>(uri, 1, 0, "QTdMessageScreenshotTaken", "C++ class");
    qmlRegisterUncreatableType<QTdMessageUnsupported>(uri, 1, 0, "QTdMessageUnsupported", "C++ class");
    qmlRegisterUncreatableType<QTdMessageVideo>(uri, 1, 0, "QTdMessageVideo", "C++ class");
    qmlRegisterUncreatableType<QTdMessageVideoNote>(uri, 1, 0, "QTdMessageVideoNote", "C++ class");
    qmlRegisterUncreatableType<QTdMessageVoiceNote>(uri, 1, 0, "QTdMessageVoiceNote", "C++ class");
    qmlRegisterUncreatableType<QTdFormattedText>(uri, 1, 0, "QTdFormattedText", "C++ class");
    qmlRegisterUncreatableType<QTdWebPage>(uri, 1, 0, "QTdWebPage", "C++ class");
    qmlRegisterUncreatableType<QTdContact>(uri, 1, 0, "QTdContact", "c++ class");
    qmlRegisterUncreatableType<QTdMessageContact>(uri, 1, 0, "QTdMessageContact", "C++ class");

    // Settings
    qmlRegisterUncreatableType<QTdProxy>(uri, 1, 0, "QTdProxy", "C++ class");
    qmlRegisterUncreatableType<QTdProxyType>(uri, 1, 0, "QTdProxyType", "C++ class");

    // stickers
    qmlRegisterUncreatableType<QTdStickerSet>(uri, 1, 0, "QTdStickerSet", "C++ class");
}
