import QtQuick 2.9
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3 as UITK_Popups
import QtQuick.Controls.Suru 2.2
import QtQuick.Layouts 1.1
import QTelegram 1.0
import "../actions"
import "../components"
import "../stores"


Page {
    id: chatInfoPage

    property bool isGroup: false
    property QTdUser user: null
    property QTdChat chat: null

    header: UITK.PageHeader {
        title: chatInfoPage.isGroup ? i18n.tr('Group Details') : i18n.tr('Profile')

        leadingActionBar.actions: [
        BackAction {
            enableShortcut: pageStack.currentItem == chatInfoPage
            onTriggered: {
                AppActions.view.popFromStack()
            }
        }
        ]
        trailingActionBar.actions: [
        UITK.Action {
            iconName: "edit"
            text: i18n.tr('Edit')
            visible: !isGroup
            onTriggered: UITK_Popups.PopupUtils.open(editUserDialog)
        },
        UITK.Action {
            iconName: "message"
            text: i18n.tr('Send message')
            visible: !isGroup
            onTriggered: {
                AppActions.chat.closeCurrentChat()
                AppActions.chat.createOrOpenPrivateChat(user)
            }
        }
        ]
        UITK.StyleHints {
            backgroundColor: dumb_color.color
        }
        Item {
            id: dumb_color
            Suru.highlightType: Suru.PositiveHighlight
            property color color: chat && chat.isSecret ? Qt.tint(Suru.backgroundColor, Qt.rgba(Suru.highlightColor.r, Suru.highlightColor.g, Suru.highlightColor.b, 0.4)) : Suru.backgroundColor
        }
    }
    Component {
        id: editUserDialog
        PopupDialog {
            text: i18n.tr("Edit user data and press Save")
            confirmButtonColor: theme.palette.normal.positive
            confirmButtonText: i18n.tr("Save")
            onConfirmed: AppActions.user.addUser(userName.text, firstName.text, lastName.text)
            UITK.TextField {
                anchors {
                    left: parent.left
                    right: parent.right
                }
                id: userName
                text: user.phoneNumber ? '+' + user.phoneNumber : i18n.tr("Hidden Number")
                readOnly: true
            }
            UITK.TextField {
                anchors {
                    left: parent.left
                    right: parent.right
                }
                id: firstName
                text: user.firstName
                placeholderText: i18n.tr("First name")
            }
            UITK.TextField {
                anchors {
                    left: parent.left
                    right: parent.right
                }
                id: lastName
                text: user.lastName
                placeholderText: i18n.tr("Last name")
            }
        }
    }


    Flickable {
        id: chatInfoFlickable
        anchors.fill: parent
        anchors.margins: Suru.units.gu(2)
        contentHeight: chatInfoColumn.height

        ColumnLayout {
            id: chatInfoColumn
            width: parent.width
            spacing: 0

            UserProfile {
                Layout.fillWidth: true
                user: chatInfoPage.user
                chat: chatInfoPage.chat
                isGroup: chatInfoPage.isGroup
                parentMargins: chatInfoFlickable.anchors.margins

                UITK.ListItem {
                    width: parent.width
                    height: notificationDelegate.height
                    visible: chat && !chat.isMyself
                    onClicked: switchDelegate.toggle()
                    UITK.ListItemLayout {
                        id: notificationDelegate
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "notification"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title {
                            text: i18n.tr("Notifications")
                            wrapMode: Text.Wrap
                            maximumLineCount: 2
                            elide: Text.ElideRight
                        }
                        Switch {
                            id: switchDelegate
                            checked: isMuted
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Trailing
                            Suru.highlightType: Suru.PositiveHighlight
                            onCheckedChanged: if (visible) {AppActions.chat.muteChat(chat, checked ? 0 : 574410023)}
                            property bool isMuted: visible ? !chat.isMuted : true
                        }
                    }
                }
                UITK.ListItem {
                    width: parent.width
                    height: commonGroups.height
                    visible: !isGroup && (chat ? !chat.isMyself : true)
                    UITK.ListItemLayout {
                        id: commonGroups
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "contact-group"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title {
                            text: visible ? i18n.tr("%1 group in common", "%1 groups in common", user.fullInfo.groupInCommonCount).arg(user.fullInfo.groupInCommonCount) : ""
                            wrapMode: Text.Wrap
                            maximumLineCount: 2
                            elide: Text.ElideRight
                        }
                    }
                }
                UITK.ListItem {
                    width: parent.width
                    height: secretHashLink.height
                    visible: chat && chat.isSecret
                    onClicked: AppActions.view.pushToStack("qrc:///pages/SecretChatKeyHashPage.qml", {
                        "keyHashMap": chat.keyHashMap,
                        "keyHashString": chat.keyHashString,
                        "userFirstName": user.firstName
                    })
                    UITK.ListItemLayout {
                        id: secretHashLink
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "system-lock-screen"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title.text: i18n.tr("Encryption Key")
                        UITK.ProgressionSlot {}
                    }
                }
                UITK.ListItem {
                    width: parent.width
                    height: ttlSetter.height
                    visible: chat && chat.isSecret
                    onClicked: AppActions.chat.setTTL(chat)
                    UITK.ListItemLayout {
                        id: ttlSetter
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "burn-after-read"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title.text: i18n.tr("Set self-destruct timer")
                    }
                }
            }
        }
    }
}
