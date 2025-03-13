import QtQuick 2.4
import QuickFlux 1.1
import "./"

ActionCreator {
    signal setCurrentChat(var chat)
    signal createOrOpenPrivateChat(var user)
    signal createOrOpenSecretChat(var user)
    signal createOrOpenSavedMessages()
    signal setCurrentChatById(string chatId)
    signal setCurrentChatByUsername(string username)
    signal closeCurrentChat()

    signal loadMoreChats();
    signal loadNewerMessages();
    signal loadOlderMessages();

    signal sendMessage(string text);
    signal showSendMessageWithOptions(string text, string replyId);
    signal sendMessageWithOptions(string text, bool disableNotification, int sendDate, string replyId);
    signal sendPhoto(string url, string text, string replyId);
    signal sendPhotoAlbum(var urls, string captionText, string replyId);
    signal sendVideo(string url, string text, string replyId);
    signal sendVideoAlbum(var urls, string captionText, string replyId);
    signal sendAudio(string url, string text, string replyId);
    signal sendAudioAlbum(var urls, string captionText, string replyId);
    signal sendContact(string url, string replyId);
    signal sendContactParsed(string firstName, string lastName, string phone, string replyId);
    signal sendDocument(string url, string text, string replyId);
    signal sendDocumentAlbum(var urls, string captionText, string replyId);
    signal sendSticker(var sticker, string replyId);
    signal sendVoiceNote(string filename, string replyId);
    signal sendLocation(double latitude, double longitude, int livePeriod, string replyId);
    signal requestLocation();
    signal cancelLocation();
    signal stopWaitLocation();
    signal sendChatAction();

    signal leaveChat(string chatId);
    signal deleteChatHistory(string chatId);

    signal deleteMessage(string id, bool forAllUsers)
    signal forwardMessage(string id)
    signal sendForwardMessage(var chat, string text)
    signal importFromContentHub(var contentType, var filePaths)
    signal sendImportData(var chat, string text)
    signal cancelForwardMessage()
    signal requestEditMessage(var message)
    signal sendEditMessageText(string id, string text)
    signal sendEditMessageCaption(string id, string text)
    signal requestReplyToMessage(var message)
    signal clearReply()
    signal sendReplyToMessage(string id, string text)
    signal showStickerPack(string stickerId)
    signal setChatDraftMessage(string draftText, string replyToMessageId)

    signal muteChat(var chat, int duration)
    signal toggleFilterBar()
    signal setChatListFilter(int chatListFilterIndex)
    signal registerVoiceNote(string filename)
    signal stopVoiceNote()
    signal deleteVoiceNote(string filename)
    signal checkChatInviteLink(var inviteLink)
    signal joinChatByInviteLink(var inviteLink)
    signal joinChat()
    signal searchChat(string searchText)
    signal openMessageContent(string chatId, string messageId)
    signal setTTL(var chat)
    signal sendSetTTL(string id, int ttl)
    signal setPollAnswer(string chatId, string messageId, var optionIds)
    signal clearCitationStack()
    signal pushCitationStack(string messageId)
    signal jumpToLastWithCitationStack()
    signal jumpToMessage(string id, bool isToBeHighlighted)

    signal removeChatActionBar()
    signal reportChat(string id, var reason, string text)
    signal pinChat(string id)
    signal unpinChat(string id)
    signal requestMessageLink(string chatId, string messageId)

    function viewGroupInfo(chat) {
        view.pushToStack("qrc:/pages/ChatInfoPage.qml", {
                             chat: chat,
                             isGroup: true
                         })
    }
}
