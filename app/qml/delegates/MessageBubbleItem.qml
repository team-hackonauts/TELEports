import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3 as UITK_Popups
import QTelegram 1.0

import "../components"
import "../actions"
import "../stores"

UITK.ListItem {
    id: base
    width: parent.width
    height: contentCol.height + row.anchors.topMargin + row.anchors.bottomMargin
    divider.visible: false

    property QTdMessage message: null
    property QTdChat chat: null
    property bool indicatorsEnabled: false
    property bool transparentBackground: false
    // multimediaLayout: this property is used to display the date/time of sending inside a photo/video/etc... instead as another row at the bottom of the message.
    property bool multimediaLayout: false
    property real mcMargins: Suru.units.dp(5)
    property real maximumAvailableContentWidth: maxAvailableWidthNoMargins - mc.horizontalMargins
    property real maxAvailableWidthNoMargins: Math.min(Suru.units.gu(55), width * (3/4))
    property alias senderLabelVisible: senderLabel.visible

    default property alias content: mainContent.data
    highlightColor: Qt.rgba(Suru.highlightColor.r, Suru.highlightColor.g, Suru.highlightColor.b, 0.4)

    leadingActions: UITK.ListItemActions {
        actions: [
            UITK.Action {
                iconName: "delete"
                text: i18n.tr("Delete")
                onTriggered: UITK_Popups.PopupUtils.open("qrc:/components/DeleteDialog.qml", base, {message:base.message, chat: base.chat})

                visible: message && (message.canBeDeletedOnlyForSelf || message.canBeDeletedForAllUsers)
            }
        ]
    }

    trailingActions: UITK.ListItemActions {
        actions: [
            UITK.Action {
                iconName: "edit-copy"
                text: i18n.tr("Copy")
                visible: message && message.content.type == QTdObject.MESSAGE_TEXT
                onTriggered: {
                    var mimeData = UITK.Clipboard.newData();
                    mimeData.text = message.content.text.text;
                    UITK.Clipboard.push(mimeData);
                }
            },
            UITK.Action {
                iconName: "edit"
                text: i18n.tr("Edit")
                visible: message && message.canBeEdited
                onTriggered: {
                    AppActions.chat.requestEditMessage(message)
                }
            },
            UITK.Action {
                iconName: "mail-reply"
                text: i18n.tr("Reply")
                visible: message && !message.isChannelPost
                onTriggered: AppActions.chat.requestReplyToMessage(message)
            },
            UITK.Action {
                iconName: "info"
                text: i18n.tr("Sticker Pack info")
                visible: message && message.content.type === QTdObject.MESSAGE_STICKER
                onTriggered: AppActions.chat.showStickerPack(message.content.sticker.setId)
            },
            UITK.Action {
                //enabled only for public groups/channels, where everyone has got access
                iconName: "stock_link"
                text: i18n.tr("Copy link")
                visible: message && chat.userName != null && chat.userName != ""
                onTriggered: {
                    AppActions.chat.requestMessageLink(chat.id, message.id)
                }
            },
            UITK.Action {
                iconName: "next"
                text: i18n.tr("Forward")
                visible: message && message.canBeForwarded
                onTriggered: AppActions.chat.forwardMessage([message.id])
            }
        ]
    }

    RowLayout {
        id: row
        anchors {
            fill: parent
            margins: Suru.units.gu(1)
            topMargin: message && message.sameSenderAsNextMessage && !message.isLatest ? Suru.units.dp(2) : Suru.units.dp(3)
            bottomMargin: message && message.sameSenderAsPreviousMessage && !message.isLatest ? Suru.units.dp(2) : Suru.units.dp(3)
        }

        Item {
            width: Suru.units.gu(4.5)
            height: Suru.units.gu(4.5)
            Layout.alignment: Qt.AlignBottom | Qt.AlignLeft
            visible: message && !(message.isOutgoing || chat.isPrivate || chat.isSecret || chat.isChannel)

            GenericPhoto {
                visible: message && !message.sameSenderAsPreviousMessage
                anchors.fill: parent
                photoPath: message && message.sender.smallPhotoPath
                initials: message && message.sender.initials
                avatarColor: message && message.sender.avatarColor
            }
            MouseArea {
                anchors.fill: parent
                // TODO: handle non-user sender
                onClicked: {
                    if (!message.sender.user) {
                        return;
                    }

                    AppActions.user.showUserInfo(message.sender.user, null);
                }
            }
        }

        Rectangle {
            id: contentCol
            color: {
                if (transparentBackground) {
                    return "transparent"
                }
                if (message && message.isOutgoing) {
                    if (message.content.type === QTdObject.MESSAGE_CALL) {
                        return Suru.secondaryBackgroundColor
                    }
                    if (message.sendingState) {
                        if (message.sendingState.type===QTdObject.MESSAGE_SENDING_STATE_PENDING) { // unsent
                            return Suru.neutralColor
                        } else if (message.sendingState.type===QTdObject.MESSAGE_SENDING_STATE_FAILED) {  //failed
                            var failedcolor = Suru.theme == Suru.Dark ? Suru.lightNegative : Suru.darkNegative
                            return Qt.tint(Suru.backgroundColor, Qt.rgba(failedcolor.r, failedcolor.g, failedcolor.b, 0.5))
                        }
                    } else if (message.id > chat.lastReadOutboxMessageId) { //sent
                        var sentcolor = Suru.theme == Suru.Dark ? Suru.lightInformation : Suru.darkInformation
                        return Qt.tint(Suru.backgroundColor, Qt.rgba(sentcolor.r, sentcolor.g, sentcolor.b, 0.5))
                    } // read
                    var readcolor = Suru.theme == Suru.Dark ? Suru.lightPositive : Suru.darkPositive
                    return Qt.tint(Suru.backgroundColor, Qt.rgba(readcolor.r, readcolor.g, readcolor.b, 0.5))
                } //incoming
                return Suru.secondaryBackgroundColor
            }

            radius: Suru.units.dp(4)
            Layout.alignment: message && message.isOutgoing ? Qt.AlignRight : Qt.AlignLeft
            Layout.minimumWidth: Math.min(maxAvailableWidthNoMargins, mc.width + mc.horizontalMargins)
            Layout.maximumWidth: Layout.minimumWidth
            Layout.preferredHeight: mc.height

            Rectangle {
               width: contentCol.width
               height: contentCol.height
               radius: contentCol.radius
               y: units.dp(1)
               z: -5
               visible: !transparentBackground
               color: Suru.neutralColor    // (i.e. Silk, #CDCDCD) (#e6e6e6) with opacity: 0.5
            }

            Column {
                id: mc

                anchors {
                    top: parent.top
                    topMargin: mcMargins
                    left: message && !message.isOutgoing ? parent.left : undefined
                    leftMargin: mcMargins
                    right: message && message.isOutgoing ? parent.right: undefined
                    rightMargin: mcMargins
                }

                property real horizontalMargins: mc.anchors.leftMargin + mc.anchors.rightMargin

                width: Math.min(maximumAvailableContentWidth,
                                Math.max(mainContent.width,
                                         message_status_comp.implicitWidth,senderLabel.contentWidth+units.gu(1)))
                height: childrenRect.height

                Item {
                    visible: message && (!(message.isOutgoing || chat.isPrivate || chat.isSecret) && !message.sameSenderAsNextMessage)
                    width: parent.width
                    height: Suru.units.gu(mcMargins == 0 ? 3 : 2.5)

                    RowLayout {
                        id: topBar
                        anchors.fill: parent
                        Layout.maximumWidth: maximumAvailableContentWidth
                        Label {
                            Layout.fillWidth: true
                            id: senderLabel
                            text: message && message.sender ? message.sender.fullName : ""
                            font.bold: false
                            elide: Text.ElideRight
                            wrapMode: Text.NoWrap
                            color: message && message.sender ? message.sender.avatarColor : ""
                            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                            Layout.leftMargin: mcMargins == 0 ? Suru.units.dp(5) : 0
                        }
                    }
                }

                Item {
                    id: mainContent
                    height: children ? childrenRect.height : 0
                    width: childrenRect.width
                }

                Item {
                    height: visible ? Suru.units.gu(2.5) : 0
                    width: parent.width
                    visible: !multimediaLayout

                    MessageStatusRow {
                        id: message_status_comp
                        anchors {
                            right: parent.right
                            rightMargin: mcMargins == 0 ? Suru.units.dp(5) : 0
                        }

                        MessageStatusIndicator {
                            bgColor: contentCol.color
                            enabled: base.indicatorsEnabled
                            statusMessage: message
                        }
                    }
                }
            }
        }

        Item {
            Layout.fillWidth: message && !message.isOutgoing
        }
    }

    ColorAnimation {
        id: highlightAnimation
        target: base
        property: "color"
        easing.type: Easing.OutSine
        from: base.highlightColor
        to: "transparent"
        duration: 4000
    }
    function highlight() {
        highlightAnimation.complete()
        highlightAnimation.start()
    }
}
