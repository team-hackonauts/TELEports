import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Lomiri.Content 1.3
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3 as UITK_Popups
import QuickFlux 1.1
import QTelegram 1.0
import "../components"
import "../actions"
import "../stores"
import "pageutils.js" as PageUtils

Page {
    id: chatListPage
    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor
    property bool importInProgress: false
    property var activeTransfer: null
    property var importFileStatus: new Map()

    header: UITK.PageHeader {

        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }

        leadingActionBar.actions: [
            UITK.Action {
                text: i18n.tr("Cancel")
                iconName: "cancel"
                shortcut: StandardKey.Cancel
                onTriggered: AppActions.chat.cancelForwardMessage()
                visible: Telegram.chats.listMode == ChatList.ForwardingMessages
                        || Telegram.chats.listMode == ChatList.ImportingAttachments
            },
            UITK.Action {
                text: i18n.tr("Settings")
                iconName: "navigation-menu"
                onTriggered: {
                    mainMenuPanel.visible ? mainMenuPanel.close() : mainMenuPanel.open()
                }
                visible: Telegram.chats.listMode == ChatList.Idle
            }
        ]
        trailingActionBar.actions: [
            UITK.Action {
                iconName: "filters"
                onTriggered: AppActions.chat.toggleFilterBar()
            }
        ]
        contents: Item {
            anchors.fill: parent
            Item {
                id: searchBox
                anchors.fill: parent
                TextField {
                    id: searchText
                    anchors.fill: parent
                    anchors.margins: Suru.units.gu(1)
                    placeholderText: i18n.tr("Search")
                    onTextChanged: searchTimer.restart()
                    inputMethodHints: Qt.ImhNoPredictiveText
                }
                UITK.Icon {
                    anchors.right: searchText.right
                    anchors.margins: Suru.units.gu(1)
                    anchors.verticalCenter: parent.verticalCenter
                    color: hf
                    width: units.gu(3)
                    height: width
                    name: "edit-clear"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            searchTimer.stop()
                            searchText.text = ""
                            AppActions.chat.searchChat("")
                        }
                    }
                    visible: searchText.text.length > 0
                }
                Timer {
                    id: searchTimer
                    interval: 500;
                    running: false;
                    repeat: false;
                    onTriggered: {
                        AppActions.chat.searchChat(searchText.text)
                    }
                }
            }
            Label {
                anchors.centerIn: parent
                text: header.title
                color: hf
            }
        }

        extension: UITK.Sections {
            height: Telegram.chats.chatFilterBarVisible ? Suru.units.gu(5) : 0
            visible: Telegram.chats.chatFilterBarVisible
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: units.gu(2)
                rightMargin: anchors.leftMargin
                bottom: parent.bottom
            }
            model: [ i18n.tr("All"), i18n.tr("Personal"), i18n.tr("Unread"), i18n.tr("Archived") ]
            onSelectedIndexChanged: {
                AppActions.chat.setChatListFilter(selectedIndex);
            }
            Behavior on height { UITK.LomiriNumberAnimation {} }
        }
    }

    Menu {
        id: mainMenuPanel
        width: parent.width * 0.75
        Suru.theme: rootItem.Suru.theme
        MenuPanelItem {
            iconName: "inbox"
            label: i18n.tr("Saved Messages")
            onTriggered: AppActions.chat.createOrOpenSavedMessages()
        }
        MenuPanelItem {
            iconName: "address-book-app-symbolic"
            label: i18n.tr("Contacts")
            onTriggered: AppActions.settings.viewUserList()
        }
        MenuPanelItem {
            iconName: "settings"
            label: i18n.tr("Settings")
            onTriggered: AppActions.view.pushToStack("qrc:/pages/SettingsPage.qml", {})
        }
        MenuPanelItem {
            id: nightModeMenuItem
            iconName: "night-mode"
            RowLayout {
                anchors.right: parent.right
                anchors.rightMargin: units.gu(2)
                anchors.left: parent.left
                anchors.leftMargin: units.gu(5)
                anchors.verticalCenter: parent.verticalCenter
                spacing: units.gu(1)
                Button {
                    text: i18n.tr("System")
                    highlighted: Telegram.settingsStore.uitkTheme == ""
                    Layout.maximumWidth: units.gu(10)
                    onClicked: {
                        AppActions.settings.setTheme(Suru.System)
                        mainMenuPanel.close()
                    }
                }
                Button {
                    text: i18n.tr("Dark")
                    highlighted: Telegram.settingsStore.uitkTheme == "Lomiri.Components.Themes.SuruDark"
                    Layout.maximumWidth: units.gu(10)
                    onClicked: {
                        AppActions.settings.setTheme(Suru.Dark)
                        mainMenuPanel.close()
                    }
                }
                Button {
                    text: i18n.tr("Light")
                    highlighted: Telegram.settingsStore.uitkTheme == "Lomiri.Components.Themes.Ambiance"
                    Layout.maximumWidth: units.gu(10)
                    onClicked: {
                        AppActions.settings.setTheme(Suru.Light)
                        mainMenuPanel.close()
                    }
                }
            }
        }
        MenuPanelItem {
            iconName: "help"
            label: i18n.tr("About")
            onTriggered: AppActions.view.pushToStack("qrc:///pages/AboutPage.qml", {})
        }
    }


    WaitingBar {
        id: waitingBar
        connectionState: Telegram.connections.connectionState
        z: 10
    }

    FlyingButton {
        onClicked: {
            chatList.currentIndex = 0;
            chatList.positionViewAtBeginning();
        }
        iconName: "toolkit_chevron-up_3gu"
        visibleState: !chatList.atYBeginning
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: units.gu(1)
        EmbeddedNotification {
            displayText: i18n.tr("Select destination:")
            displaySubText: i18n.tr("or cancel the operation")
            Layout.preferredHeight: implicitHeight
            Layout.fillWidth: true
            closeable: false
            visible: Telegram.chats.listMode == ChatList.ForwardingMessages
                        || Telegram.chats.listMode == ChatList.ImportingAttachments
        }
        ScrollView {
            id: chatListScrollView
            Layout.fillHeight: true
            Layout.fillWidth: true
            ListView {
                id:chatList
                clip: true
                anchors{
                    fill: parent
                }

                // WORKAROUND: Fix for wrong grid unit size
                Component.onCompleted: root.flickable_responsive_scroll_fix(chatList)

                model: Telegram.chats.sortedList
                delegate: UITK.ListItem {

                    readonly property QTdChat chat: modelData
                    property QTdChat userSelectedChat
                    width: parent.width
                    height: layout.height
                    Suru.highlightType: Suru.PositiveHighlight
                    color: chat.isSecret ? Qt.rgba(Suru.highlightColor.r, Suru.highlightColor.g, Suru.highlightColor.b, 0.4) : "transparent"

                    onClicked: {
                        if (Telegram.chats.listMode == ChatList.ForwardingMessages) {
                            userSelectedChat = chat;
                            UITK_Popups.PopupUtils.open(forwardConfirmationDialog);
                        } else if (Telegram.chats.listMode == ChatList.ImportingAttachments) {
                            userSelectedChat = chat;
                            AppActions.chat.sendImportData(userSelectedChat, incomingTextFromContentHub);
                            incomingTextFromContentHub  = ''
                        } else {
                            if (searchText.text !== "") {
                                searchTimer.stop();
                                searchText.text = "";
                            }
                            AppActions.chat.setCurrentChat(chat);
                        }
                    }

                    leadingActions: UITK.ListItemActions {
                        actions: [
                            UITK.Action {
                                iconName: "system-log-out"
                                text: i18n.tr("Leave chat")
                                onTriggered: AppActions.chat.leaveChat(chat.id)
                            },
                            UITK.Action {
                                iconName: "edit-clear"
                                text: i18n.tr("Clear history")
                                visible: chat.isPrivate
                                onTriggered: AppActions.chat.deleteChatHistory(chat.id)
                            }
                        ]
                    }

                    trailingActions: UITK.ListItemActions {
                        actions: [
                            UITK.Action {
                                iconName: "info"
                                text: i18n.tr("Info")
                                onTriggered: chat.isPrivate ? AppActions.user.showUserInfo(chat.chatType.user, chat) : AppActions.chat.viewGroupInfo(chat)
                            },
                            UITK.Action {
                                iconName: chat.isPinned ? "unpinned" : "pinned"
                                text: i18n.tr("Un/pin")
                                onTriggered: chat.isPinned ? AppActions.chat.unpinChat(chat.id) : AppActions.chat.pinChat(chat.id)
                            }
                        ]
                    }

                    UITK.SlotsLayout {
                        id: layout

                        GenericPhoto {
                            isUser: chat.isSecret || chat.isPrivate
                            isOnline: isUser ? chat.chatType.user.isOnline && !chat.chatType.user.isBot && !chat.chatType.user.isMyself : false 
                            id: avatar
                            height: units.gu(6)
                            width: height
                            photoPath: chat.smallPhotoPath
                            initials: chat.initials
                            avatarColor: chat.avatarColor(chat ? chat.rawId : 0)
                            myself: chat ? chat.isMyself : false
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                            UITK.SlotsLayout.padding.trailing: 0
                        }

                        mainSlot: Item {
                            height: col.height

                            Column {
                                id: col
                                anchors {
                                    left: parent.left
                                    right: parent.right
                                    top: parent.top
                                }
                                spacing: units.gu(1)

                                RowLayout {
                                    height: units.dp(17)
                                    width: parent.width
                                    spacing: units.dp(2)

                                    UITK.Icon {
                                        id: secret_chat_icon
                                        visible: chat.isSecret //if chat is encrypted
                                        name: "network-secure"
                                        color: Suru.foregroundColor
                                        Suru.textStyle: Suru.TertiaryText
                                        height: units.gu(2)
                                        width: height
                                    }

                                    UITK.Icon {
                                        id: contact_group_icon
                                        visible: chat.isGroup //if chat is a real chat or a supergroup, but not channel
                                        name: "contact-group"
                                        color: Suru.foregroundColor
                                        Suru.textStyle: Suru.TertiaryText
                                        height: units.gu(2)
                                        width: height
                                    }

                                    UITK.Icon {
                                        id: contact_channel_icon
                                        visible: chat.isChannel //if chat is channel but not supergroup
                                        source: "qrc:/qml/icons/broadcast.svg"
                                        color: Suru.foregroundColor
                                        Suru.textStyle: Suru.TertiaryText
                                        height: units.gu(2)
                                        width: height
                                    }

                                    UITK.Icon {
                                        id: contact_bot_icon
                                        visible: chat.isBot //if chat is peer is a bot
                                        source: "qrc:/qml/icons/bot.svg"
                                        color: Suru.foregroundColor
                                        Suru.textStyle: Suru.TertiaryText
                                        height: units.gu(2)
                                        width: height
                                    }

                                    UITK.Icon {
                                        id: audio_volume_muted_icon
                                        visible: chat.isMuted
                                        name: "audio-volume-muted"
                                        color: Suru.foregroundColor
                                        Suru.textStyle: Suru.TertiaryText
                                        height: units.gu(2)
                                        width: height
                                    }

                                    Label {
                                        id: title
                                        elide: Text.ElideRight
                                        wrapMode: Text.WrapAnywhere
                                        maximumLineCount: 1
                                        font.weight: Font.DemiBold
                                        font.pixelSize: units.dp(17)
                                        text: chat.title
                                        Layout.fillWidth: true
                                        Layout.alignment: Qt.AlignVCenter
                                    }
                                }

                                RowLayout {
                                    height: units.gu(2)
                                    width: parent.width
                                    Label {
                                        visible: chat.summary[0] != ""
                                        font.pixelSize: units.dp(15)
                                        Suru.textStyle: Suru.TertiaryText
                                        Suru.highlightType: Suru.NegativeHighlight
                                        color: Suru.highlightColor
                                        text: chat.summary[0]
                                    }
                                    Label {
                                        elide: Text.ElideRight
                                        maximumLineCount: 1
                                        font.pixelSize: units.dp(15)
                                        Suru.textStyle: Suru.TertiaryText
                                        text: chat.summary[1]
                                        Layout.fillWidth: true
                                    }
                                }
                            }
                        }

                        Item {
                            width: Math.max(time_text.width, icons.width)
                            height: time_text.height + icons.height
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Trailing
                            UITK.SlotsLayout.overrideVerticalPositioning: true
                            UITK.SlotsLayout.padding.leading: 0

                            UITK.Label {
                                id: time_text
                                anchors {
                                    top: parent.top
                                    topMargin: units.gu(1.5)
                                    right: parent.right
                                }

                                visible: chat.lastMessage
                                font.pixelSize: units.dp(12)
                                color: Suru.foregroundColor
                                Suru.textStyle: Suru.TertiaryText
                                text: chat.lastMessage ? chat.formatDate(chat.lastMessage.date) : ""
                            }

                            Row {
                                id: icons
                                height: unread_rect.implicitHeight
                                anchors {
                                    top: time_text.bottom
                                    topMargin: units.gu(0.5)
                                    right: parent.right
                                }
                                layoutDirection: Qt.RightToLeft
                                spacing: units.dp(2)

                                Rectangle {
                                    id: unread_rect
                                    width: Math.min(height, units.gu(4))
                                    height: units.gu(2.8)
                                    radius: width*0.5
                                    color: chat.isMuted ? Suru.neutralColor : theme.palette.normal.focus
                                    visible: chat.hasUnreadMessages

                                    Label {
                                        id: unread_text
                                        anchors {
                                            centerIn: parent
                                            margins: 0
                                        }
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.weight: Font.DemiBold
                                        font.pixelSize: FontUtils.sizeToPixels("small")
                                        color: "white"
                                        text: chat.unreadCount < 999 ? chat.unreadCount : ":D"; // no-i18n
                                    }
                                }
                                Rectangle {
                                    id: mention_rect
                                    width: Math.min(height, units.gu(4))
                                    height: units.gu(2.8)
                                    radius: width*0.5
                                    color: theme.palette.normal.focus
                                    visible: chat.hasUnreadMentions

                                    Label {
                                        id: mention_text
                                        anchors {
                                            centerIn: parent
                                            margins: 0
                                        }
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        font.weight: Font.DemiBold
                                        font.pixelSize: FontUtils.sizeToPixels("small")
                                        color: "white"
                                        text: "@"; // no-i18n
                                    }
                                }

                                UITK.Icon {
                                    id: pinned_icon
                                    anchors {
                                        top: parent.top
                                        topMargin: units.gu(0.5)
                                    }

                                    visible: chat.isPinned
                                    source: "qrc:/qml/icons/attach.svg"
                                    color: Suru.foregroundColor
                                    Suru.textStyle: Suru.TertiaryText
                                    height: units.gu(2)
                                    width: height
                                }
                            }
                        }
                        Component {
                            id: forwardConfirmationDialog
                            PopupDialog {
                                text: i18n.tr("Do you want to forward the selected messages to %1?").arg(userSelectedChat.title)
                                confirmButtonColor: theme.palette.normal.focus
                                confirmButtonText: i18n.tr("Forward")
                                onConfirmed: {
                                    var optionalMessageText = optionalMessage.text.trim();
                                    AppActions.chat.sendForwardMessage(userSelectedChat, optionalMessageText);
                                }
                                UITK.TextArea {
                                    height: units.gu(10)
                                    autoSize: true
                                    anchors {
                                        left: parent.left
                                        right: parent.right
                                    }
                                    id: optionalMessage
                                    placeholderText: i18n.tr("Enter optional message...")
                                }
                            }
                        }

                        Component {
                            id: importConfirmationDialog
                            PopupDialog {
                                text: i18n.tr("Do you want to send the imported text to %1?").arg(userSelectedChat.title)
                                confirmButtonColor: theme.palette.normal.focus
                                confirmButtonText: i18n.tr("Send")
                                onConfirmed: {
                                    var optionalMessageText = optionalMessage.text.trim();
                                    AppActions.chat.sendImportData(userSelectedChat, optionalMessageText);
                                }
                                UITK.TextArea {
                                    height: units.gu(10)
                                    autoSize: true
                                    anchors {
                                        left: parent.left
                                        right: parent.right
                                        topMargin: units.gu(0.1)
                                    }
                                    id: optionalMessage
                                    placeholderText: i18n.tr("Enter optional message...")
                                    text: incomingTextFromContentHub
                                }
                            }
                        }
                    }

                }

                visibleArea.onYPositionChanged: {
                    if (visibleArea.yPosition > 1 - visibleArea.heightRatio - 0.05 && model.count > 5) {
                        console.log("chat list scrolled to the end, loading more chats");
                        AppActions.chat.loadMoreChats()
                    }
                }
            }

            Component.onCompleted : {
                AppActions.chat.loadMoreChats();
            }
        }
    }

    property string incomingTextFromContentHub: ""
    function processContentHubIncoming(transfer) {
        activeTransfer = transfer;
        if (transfer.contentType === ContentType.Links || transfer.contentType === ContentType.Text) {
            var message = ""
            for (var i = 0; i < transfer.items.length; i++) {
                if (String(transfer.items[i].text).length > 0) {
                    message += String(transfer.items[i].text)
                    message += "\n"
                }
                if (String(transfer.items[i].url).length > 0) {
                    message += String(transfer.items[i].url)
                    message += "\n"
                }
            }
            incomingTextFromContentHub = message.trim()
            AppActions.chat.importFromContentHub(transfer.contentType, [""]) // dummy filename list with length = 1
        } else {
            const fileNames = [ ];
            importInProgress = true;
            importFileStatus.clear();
            for ( let i = 0; i < transfer.items.length; i++ ) {
                const fileName = String(transfer.items[i].url);
                fileNames.push(fileName);
                importFileStatus.set(fileName, false);
                console.log("request file ", fileName);
            }
            AppActions.chat.importFromContentHub(transfer.contentType, fileNames);
        }
    }

    Connections {
        target: ContentHub
        onImportRequested: processContentHubIncoming(transfer)
        onShareRequested: processContentHubIncoming(transfer)
    }

    Connections {
        target: Telegram.chats.messageListController
        onImportFileFinished: (fileName) => {
            if (importInProgress !== true) {
                return;
            }
            if (PageUtils.isFinishedTransferAfter(fileName, importFileStatus)) {
                activeTransfer.finalize();
                activeTransfer = null;
                importInProgress = false;
            }
        }
    }
}
