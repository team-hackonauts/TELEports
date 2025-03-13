import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QTelegram 1.0
import "../stores"
import "../actions"

Item {
    property QTdMessage messageCited: null

    height: column.height + Suru.units.gu(0.5)
    width: Math.min(maximumAvailableContentWidth, childrenRect.width)

    Rectangle {
        id: colorBlock
        anchors {
            left: parent.left
            top: parent.top
        }
        width: Suru.units.dp(3)
        height: parent.height - Suru.units.gu(0.5)
        color: Suru.foregroundColor
        opacity: 0.8
    }

    Column {
        id: column

        spacing: 0

        anchors {
            left: colorBlock.right
            leftMargin: Suru.units.gu(1)
            top: parent.top
        }

        Label {
            id: senderLabel
            height: Suru.units.gu(2.5)
            width: maximumAvailableContentWidth
            text: messageCited.sender && messageCited.rawId > 0 ? messageCited.sender.fullName : ""
            elide: Text.ElideRight
            font.bold: false
            color: messageCited.sender && messageCited.rawId > 0 ? messageCited.sender.avatarColor : ""
        }

        TextMetrics {
            id: senderNameMetrics
            text: senderLabel.text
        }

        Loader {
            id: loader
            active: (messageCited != null)
            Component.onCompleted: (messageCited && messageCited.rawId > 0 && messageCited.content) ?
                                        setSource(contentDelegateMap.findComponent(messageCited.content.type), {message: messageCited}) :
                                        setSource("qrc:///delegates/MessageUnavailable.qml")
        }
    }

    MouseArea {
        id: citationControl
        anchors.fill: parent
        enabled: parent.visible
        onClicked: {
            if (!message.messageRepliedTo || message.messageRepliedTo.rawId === 0) {
                return;
            }
            AppActions.chat.pushCitationStack(message.id);
            AppActions.chat.jumpToMessage(message.messageRepliedTo.id, true);
        }
    }
}
