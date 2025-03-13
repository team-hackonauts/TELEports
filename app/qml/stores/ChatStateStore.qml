import QtQuick 2.4
import QuickFlux 1.1
import QTelegram 1.0
import Lomiri.Content 1.1 as ContentHub
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3 as UITK_Popups
import "../actions"

Store {

    /**
     * ChatList model
     *
     * Model containing all chats for the configured account.
     * the model is not sorted in anyway but is exposed to
     * be able to access the undelying QTdChatListModel->model
     * property and it's QList like API from qml.
     *
     * If you want a sorted list use SortedChatList below.
     */
    property alias listMode: chatList.listMode
    property alias list: chatList.model
    property alias currentChat: chatList.currentChat
    property alias forwardChatId: chatList.forwardedFromChat
    property bool uriHaveBeenProcessed: false
    property bool chatFilterBarVisible: false
    property var citationStack: []

    ChatList {
        id: chatList
        onCurrentChatChanged: {
            if (currentChat && !currentChat.isOpen) {
                AppActions.view.pushToStack("qrc:/pages/MessageListPage.qml", {})
            } else {
                AppActions.view.popFromStack()
            }
        }
        onPositionInfoReceived: {
            AppActions.chat.stopWaitLocation();
            AppActions.chat.sendLocation(latitude, longitude, 0, 0);
        }
        onPositionInfoTimeout: {
            AppActions.chat.stopWaitLocation();
            AppActions.view.showError(i18n.tr("Error"), i18n.tr("No valid location received after 180 seconds!"), "");
        }
        onShowChatInviteLinkInfo: {
            AppActions.view.showChatInviteLinkInfo(info, inviteLink);
        }
        onInvalidChatUsername: {
            AppActions.view.showError(i18n.tr("Error"), i18n.tr("Username <b>@%1</b> not found").arg(username), "");
        }
        onModelPopulatedCompleted: {
            // handle URIs only the first time this signal is emitted
            if (uriHaveBeenProcessed) {
                return
            }
            if (Qt.application.arguments && Qt.application.arguments.length > 0) {
                for (var i = 1; i < Qt.application.arguments.length; i++) {
                    processUri(Qt.application.arguments[i]);
                }
            }
            uriHaveBeenProcessed = true
        }
        onShowNotification: {
            AppActions.view.showAutoCloseNotification(message)
        }
    }

    /**
     * SortedChatList model
     *
     * This model sorts chats based on a few different
     * criteria. Firstly pinned chats will always appear
     * at the top. Followed by the most recently updated
     * chats based on QTdChat::lastMessage()->date().
     *
     * This should actually be done on QTdChat::order()
     * but that seems to return an unknown order (i.e 0)
     * for anything other than supergroups/channels so
     * isn't ideal to actually be used right now.
     *
     * Filters can be applied to the model to only return
     * chat's of a certain type. chatFilters accepts OR'd flags
     *
     * e.g
     *    chatFilters: SortedChatList.PrivateChats | SortedChatList.SecretChats | SortedChatList.SuperGroups
     *
     * The above will only show chats of those three types.
     * see qtdchatlistsortfiltermodel.h for all filter types.
     */
    property alias sortedList: sortedChatList
    SortedChatList {
        id: sortedChatList
        model: chatList
    }

    /**
     *
     */
    property alias messageList: messageList.model
    property alias messageListController: messageList
    property alias chat: chatList.currentChat
    property var nextChat
    MessageList {
        id: messageList
        chat: chatList.currentChat
        // TODO: Implement UI for error handling
        onError: console.error(errorMessage)
    }

    Filter {
        type: ChatKey.setCurrentChat
        onDispatched: {
            if (message.chat) {
                if (chatList.currentChat && chatList.currentChat.isOpen  && message.chat.id !== chatList.currentChat.id) {
                    nextChat = message.chat
                    return
                }
                chatList.currentChat = message.chat
            }
        }
    }

    Filter {
        type: ChatKey.createOrOpenPrivateChat
        onDispatched: {
            if (message.user) {
                AppActions.view.popAllButOneFromStack()
                chatList.createOrOpenPrivateChat(message.user.id)
            }
        }
    }

    Filter {
        type: ChatKey.createOrOpenSavedMessages
        onDispatched: {
            AppActions.view.popAllButOneFromStack()
            chatList.createOrOpenSavedMessages()
        }
    }

    Filter {
        type: ChatKey.createOrOpenSecretChat
        onDispatched: {
            if (message.user) {
                AppActions.view.popAllButOneFromStack()
                chatList.createOrOpenSecretChat(message.user.id)
            }
        }
    }


    Filter {
        type: ChatKey.setCurrentChatById
        onDispatched: {
            var chatById = chatList.model.get(message.chatId)
            if (chatById) {
                AppActions.chat.setCurrentChat(chatById)
            } else
                console.log("Could not find chat by id")
        }
    }


    Filter {
        type: ChatKey.setCurrentChatByUsername
        onDispatched: {
            chatList.setCurrentChatByUsername(message.username)
        }
    }

    Filter {
        type: ChatKey.closeCurrentChat
        onDispatched: {
            if (chatList.currentChat && chatList.currentChat.isOpen) {
                citationStack = []
                chatList.currentChat.closeChat()
            } else
                console.log("No chat open, ignoring close request")
            if (nextChat !== null) {
                AppActions.chat.setCurrentChat(nextChat)
                nextChat = null
            }
        }
    }

    Filter {
        type: ChatKey.loadOlderMessages
        onDispatched: {
            if (d.canLoadMoreMessages) {
                messageList.loadOlder()
                d.canLoadMoreMessages = false
                enableLoadTimer.start()
            }
        }
    }
    Filter {
        type: ChatKey.loadNewerMessages
        onDispatched: {
            if (d.canLoadMoreMessages) {
                messageList.loadNewer()
                d.canLoadMoreMessages = false
                enableLoadTimer.start()
            }
        }
    }

    Filter {
        type: ChatKey.loadMoreChats
        onDispatched: {
            if (d.canLoadMoreMessages) {
                chatList.loadMoreChats("chatListMain")
                chatList.loadMoreChats("chatListArchive")
                d.canLoadMoreMessages = false
                enableLoadTimer.start()
            }
        }
    }

    Filter {
        type: ChatKey.clearCitationStack
        onDispatched: {
            citationStack = []
        }
    }

    Filter {
        type: ChatKey.pushCitationStack
        onDispatched: {
            if (Telegram.settingsStore.citationStackEnabled && (citationStack.length == 0 || citationStack[citationStack.length - 1] !== message.messageId)) {
                citationStack.push(message.messageId)
            }
        }
    }

    Filter {
        type: ChatKey.jumpToLastWithCitationStack
        onDispatched: {
            let messageToJumpTo = currentChat.lastMessage.id;
            let highlight = false;
            if (Telegram.settingsStore.citationStackEnabled && citationStack.length > 0) {
                messageToJumpTo = citationStack.pop();
                highlight = true;
            }
            AppActions.chat.jumpToMessage(messageToJumpTo, highlight);
        }
    }

    Filter {
        type: ChatKey.jumpToMessage
        onDispatched: {
            messageList.jumpToMessage(message.id, message.isToBeHighlighted);
        }
    }

    Filter {
        type: ChatKey.sendEditMessageText
        onDispatched: {
            messageList.editMessageText(message.id, message.text);
        }
    }

    Filter {
        type: ChatKey.sendEditMessageCaption
        onDispatched: {
            messageList.editMessageCaption(message.id, message.text);
        }
    }

    Filter {
        type: ChatKey.sendMessage
        onDispatched: {
            messageList.sendMessage(message.text, true);
        }
    }

    Filter {
        type: ChatKey.sendMessageWithOptions
        onDispatched: {
            messageList.sendMessage(message.text, true, message.disableNotification, message.sendDate, message.replyId)
        }
    }

    Filter {
        type: ChatKey.sendSticker
        onDispatched: {
            messageList.sendSticker(message.sticker, message.replyId);
        }
    }

    Filter {
       type: ChatKey.forwardMessage
       onDispatched: {
          chatList.forwardedFromChat = chatList.currentChat
          var messageIds = [];
          messageIds.push(message.id)
          chatList.forwardingMessages = messageIds;
          chatList.listMode = ChatList.ForwardingMessages
          AppActions.view.popFromStack()
       }
   }

    Filter {
        type: ChatKey.sendForwardMessage
        onDispatched: {
          chatList.listMode = ChatList.Idle
          AppActions.chat.setCurrentChat(message.chat);
          chatList.sendForwardMessage(chatList.forwardingMessages,
                                           message.chat.id,
                                           chatList.forwardedFromChat.id,
                                           message.text);
        }
    }
    Filter {
        type: ChatKey.cancelForwardMessage
        onDispatched: {
          AppActions.chat.setCurrentChat(chatList.forwardedFromChat)
          chatList.listMode = ChatList.Idle
        }
    }

    Filter {
        type: ChatKey.searchChat
        onDispatched: {
            sortedList.setChatNameFilter(message.searchText)
        }
    }

    property var importedFiles: []
    property var importedFileType

    Filter {
       type: ChatKey.importFromContentHub
       onDispatched: {
          chatList.forwardedFromChat = chatList.currentChat
          chatList.listMode = ChatList.ImportingAttachments
          importedFileType = message.contentType
          importedFiles = message.filePaths
          AppActions.view.popAllButOneFromStack()
       }
   }

    Filter {
        type: ChatKey.sendImportData
        onDispatched: {
            chatList.listMode = ChatList.Idle;
            AppActions.chat.setCurrentChat(message.chat);
            const fileNames = [];
            for (let i = 0; i < importedFiles.length; i++) {
                fileNames[i] = importedFileType == ContentHub.ContentType.Contacts ? importedFiles[i] : String(importedFiles[i]).replace('file://', '');
            }
            UITK_Popups.PopupUtils.open("qrc:/components/SendMediaDialog.qml", null, {mediaType: importedFileType, fileNames: fileNames, incomingText: message.text})
            importedFiles = [];
            importedFileType = "";
        }
    }

    Filter {
        type: ChatKey.sendPhoto
        onDispatched: {
            console.log("Send photo %1".arg(message.url));
            messageList.sendPhoto(message.url, message.text, message.replyId);
        }
    }

    Filter {
        type: ChatKey.sendPhotoAlbum
        onDispatched: {
            messageList.sendPhotoAlbum(message.urls, message.captionText, message.replyId);
        }
    }

    Filter {
        type: ChatKey.sendAudio
        onDispatched: {
            console.log("Send audio %1".arg(message.url));
            messageList.sendAudio(message.url, message.text, message.replyId);
        }
    }

    Filter {
        type: ChatKey.sendAudioAlbum
        onDispatched: {
            messageList.sendAudioAlbum(message.urls, message.captionText, message.replyId);
        }
    }

    Filter {
        type: ChatKey.sendVideo
        onDispatched: {
            console.log("Send video %1".arg(message.url));
            messageList.sendVideo(message.url, message.text, message.replyId);
        }
    }

    Filter {
        type: ChatKey.sendVideoAlbum
        onDispatched: {
            messageList.sendVideoAlbum(message.urls, message.captionText, message.replyId);
        }
    }

    Filter {
        type: ChatKey.sendContactParsed
        onDispatched: {
            console.log("Send contact %1 %2 %3".arg(message.firstName).arg(message.lastName).arg(message.phone));
            messageList.sendContact(message.firstName, message.lastName, message.phone, message.replyId);
        }
    }
    Filter {
        type: ChatKey.sendDocument
        onDispatched: {
            console.log("Send document %1".arg(message.url));
            messageList.sendDocument(message.url, message.text, message.replyId);
        }
    }

    Filter {
        type: ChatKey.sendDocumentAlbum
        onDispatched: {
            messageList.sendDocumentAlbum(message.urls, message.captionText, message.replyId);
        }
    }

    //Location requesting and sending
    Filter {
        type: ChatKey.requestLocation
        onDispatched: {
            chatList.requestPositionInfo();
        }
    }

    Filter {
        type: ChatKey.sendLocation
        onDispatched: {
            messageList.sendLocation(message.latitude, message.longitude, message.livePeriod, message.replyId);
        }
    }

    Filter {
        type: ChatKey.cancelLocation
        onDispatched: {
            chatList.cancelPositionInfo();
        }
    }

    Filter {
        type: ChatKey.sendReplyToMessage
        onDispatched: {
            messageList.sendMessage(message.text, true, false, 0, message.id);
        }
    }

    Filter {
        type: ChatKey.deleteMessage
        onDispatched: {
            messageList.deleteMessage(message.id, message.forAllUsers)
        }
    }

    Filter {
        type: ChatKey.sendChatAction
        onDispatched: {
            chatList.currentChat.sendChatAction(true);
        }
    }

    Filter {
        type: ChatKey.sendVoiceNote
        onDispatched: {
            console.log("Send voice note");
            messageList.sendVoiceNote(message.filename, 0);
        }
    }

    Filter {
        type: ChatKey.leaveChat
        onDispatched: {
            var chat = chatList.model.get(message.chatId)
            if (chat) {
                chat.leaveChat()
            }
        }
    }

    Filter {
        type: ChatKey.deleteChatHistory
        onDispatched: {
            var chat = chatList.model.get(message.chatId)
            if (chat) {
                chat.deleteChatHistory(false, message.forAllUsers)
            }
        }
    }

    Filter {
        type: ChatKey.setChatDraftMessage
        onDispatched: {
          chatList.setChatDraftMessage(message.draftText,
                                       message.replyToMessageId,
                                       chatList.currentChat.id);
        }
    }

    Filter {
        type: ChatKey.muteChat
        onDispatched: {
            message.chat.mute(message.duration)
        }
    }

    Filter {
        type: ChatKey.toggleFilterBar
        onDispatched: {
            chatFilterBarVisible = !chatFilterBarVisible
            sortedList.toggleFilterBar(chatFilterBarVisible)
        }
    }

    Filter {
        type: ChatKey.setChatListFilter
        onDispatched: {
            sortedList.setChatListFilter(message.chatListFilterIndex)
        }
    }

    Filter {
        type: ChatKey.registerVoiceNote
        onDispatched: {
            messageList.registerVoiceNote(message.filename)
        }
    }
    Filter {
        type: ChatKey.stopVoiceNote
        onDispatched: {
            messageList.stopVoiceNote()
        }
    }
    Filter {
        type: ChatKey.deleteVoiceNote
        onDispatched: {
            messageList.deleteVoiceNote(message.filename)
        }
    }

    Filter {
        type: ChatKey.joinChat
        onDispatched: {
            chatList.joinChat(chatList.currentChat.id);
        }
    }

    Filter {
        type: ChatKey.checkChatInviteLink
        onDispatched: {
            chatList.checkChatInviteLink(message.inviteLink);
        }
    }

    Filter {
        type: ChatKey.joinChatByInviteLink
        onDispatched: {
            AppActions.chat.closeCurrentChat()
            chatList.joinChatByInviteLink(message.inviteLink);
        }
    }

    Filter {
        type: ChatKey.openMessageContent
        onDispatched: {
            chatList.openMessageContent(message.chatId, message.messageId)
        }
    }

    Filter {
        type: ChatKey.sendSetTTL
        onDispatched: {
          chatList.sendSetTTL(message.id, message.ttl);
        }
    }

    Filter {
        type: ChatKey.removeChatActionBar
        onDispatched: {
          messageList.removeChatActionBar();
        }
    }

    Filter {
        type: ChatKey.reportChat
        onDispatched: {
          messageList.reportChat(message.id, message.reason, message.text);
        }
    }

    Filter {
        type: ChatKey.pinChat
        onDispatched: {
            chatList.togglePinChat(message.id, true);
        }
    }

    Filter {
        type: ChatKey.unpinChat
        onDispatched: {
            chatList.togglePinChat(message.id, false);
        }
    }

    Filter {
        type: ChatKey.setPollAnswer
        onDispatched: {
          chatList.setPollAnswer(message.chatId, message.messageId, message.optionIds);
        }
    }

    Filter {
        type: ChatKey.requestMessageLink
        onDispatched: {
            messageList.requestMessageLink(message.chatId, message.messageId);
        }
    }

    Timer {
        id: enableLoadTimer
        interval: 1000
        triggeredOnStart: false
        onTriggered: d.canLoadMoreMessages = true
    }

    QtObject {
        id: d
        property bool canLoadMoreMessages: true
    }

    Connections {
        target: UITK.UriHandler
        onOpened: {
            console.log('Open from UriHandler: '+uris)
            processUri(uris[0]);
        }
    }
    
    function processUri(uri) {
        if (typeof uri === "undefined") {
            return;
        }
        var protocol = uri.split(":")[0]
        switch (protocol) {
        case "teleports":
            // User clicked a notification
            var commands = uri.split("://")[1].split("/");
            if (commands) {
                switch(commands[0].toLowerCase()) {
                case "chat":
                    var chatId = parseInt(commands[1]);
                    if (isNaN(chatId) || chatId === 0) {
                        console.warn("Cannot parse chat id to open!");
                    } else {
                        console.info("Opening chat: " + chatId);
                        if (currentChat && currentChat.isOpen) {
                            if (currentChat.rawId !== chatId) {
                                AppActions.view.popFromStack()
                                AppActions.chat.setCurrentChatById(chatId)
                            }
                        } else {
                            AppActions.chat.setCurrentChatById(chatId)
                        }
                    }
                    break;
                case "launch":
                    //userTapBackHome = true;
                    // Nothing to do.
                    break
                default:
                    console.warn("Unmanaged URI: " + commands)
                }
            }
            break
        case "https":
            var tgUri = httpsToTg(uri)
            if (tgUri != undefined && tgUri != "") {
                processTgUri(tgUri)
            }
            break
        case "tg":
            processTgUri(uri)
            break
        default:
            console.log("Unhandled protocol: "+protocol+"\nPayload: "+uri.split(":")[1])
        }
    }
    /**
     * @brief httpsToTg function
     *
     * convert https URI into tg format
     */
    function httpsToTg(command) {
        if (command.startsWith("https://")) {
            command = command.substr(8)
        }
        if (command.startsWith("www.")) {
            command = command.substr(4)
        }
        if (command.startsWith("t.me/")) {
            command = command.substr(5)
        } else if (command.startsWith("telegram.me/")) {
            command = command.substr(12)
        } else if (command.startsWith("telegram.dog/")) {
            command = command.substr(13)
        } else {
            return
        }
        command = command.split("/")
        var tgUri
        switch (command[0]) {
        case "joinchat":
            // https://t.me/joinchat/XXXXXXXXXX
            tgUri = "tg://join?invite=" + command[1]
            break
        case "s":
            tgUri = `tg://resolve?domain=${command[1]}`
            break;
        case "addstickers":
        case "addtheme":
        case "setlanguage":
        case "share":
        case "confirmphone":
        case "socks":
        case "proxy":
        case "bg":
            break
        default:
            // https://t.me/<username>
            tgUri = "tg://resolve?domain=" + command[0]
            break
        }
        console.log("new uri: "+tgUri)
        return tgUri
    }

    function parseQueryParams(params) {
        const list = params.split('&');
        return list.reduce((ret, param) => {
            const [ key, value ] = param.split('=');
            ret[key] = value;
            return ret;
        }, {});
    }

    /**
     * @brief processTgUri function
     *
     * User opened a deep link to a chat or something
     */
    function processTgUri(uri) {
        let command
        if (uri.startsWith("tg://")) {
            command = uri.substr(5)
        } else if (uri.startsWith("tg:")) {
            command = uri.substr(3)
        } else {
            return
        }
        command = command.split("?")
        const args = command.length > 1 ? parseQueryParams(command[1]) : {}
        switch (command[0]) {
        case "resolve":
            // tg://resolve?domain=<username>
            const resolveArgs = command[1].split("&")
            for (let i = 0; i < resolveArgs.length; i++) {
                const param = resolveArgs[i].split("=")[0]
                const value = resolveArgs[i].split("=")[1]
                switch(param) {
                case "domain":
                    const chatId = chatList.chatIdByUsername(value)
                    if (currentChat && currentChat.isOpen && currentChat.rawId !== chatId) {
                        AppActions.view.popFromStack()
                        AppActions.chat.setCurrentChatById(chatId)
                    } else {
                        AppActions.chat.setCurrentChatById(chatId)
                    }
                    break;
                default:
                    console.log("Unhandled argument: " + args[i])
                    break
                }
            }
            break
        case "join":
            // tg://join?invite=XXXXXXXXXX
            const inviteId = args.invite
            AppActions.chat.checkChatInviteLink(inviteId)
            break
        case "proxy":
            // tg://proxy?server=<server link>&port=<port>&secret=<secret> for MTProto proxies
            // tg://proxy?proxy=<http proxy link>&port=<port>&user=<username>&pass=<password> for HTTP proxies

            const isHttp = args.server === undefined

            const mtprotoProxy = {}
            mtprotoProxy.id = -1

            mtprotoProxy.server = isHttp ? args.proxy : args.server

            mtprotoProxy.port = args.port
            mtprotoProxy.type = {}
            mtprotoProxy.type.type = isHttp ? 0 : 1 // 0 is HTTP, 1 is MTProto, 2 is SOCKS5

            if (!isHttp) {
                mtprotoProxy.type.secret = args.secret
            }

            if (isHttp) {
                mtprotoProxy.type.username = args.user
                mtprotoProxy.type.password = args.pass
            }

            AppActions.view.pushToStack("qrc:/pages/settings/AddOrEditProxyPage.qml", {proxy: mtprotoProxy})
            break
        case "socks":
            // tg://socks?server=<server link>&port=<port> for SOCKS5 proxies

            const socksProxy = {}
            socksProxy.id = -1
            socksProxy.server = args.server
            socksProxy.port = args.port
            socksProxy.type = {}
            socksProxy.type.type = 2
            
            if (args.user.length > 0) {
                socksProxy.type.username = args.user
            }

            if (args.pass.length > 0) {
                socksProxy.type.password = args.pass
            }

            AppActions.view.pushToStack("qrc:/pages/settings/AddOrEditProxyPage.qml", {proxy: socksProxy})
            break
        default:
            console.log("Unhandled command: " + command)
        }
    }
}
