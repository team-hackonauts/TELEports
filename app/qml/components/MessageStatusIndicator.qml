import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QtGraphicalEffects 1.0
import QTelegram 1.0

Item {
    id: messageStatusIndicator
    anchors.verticalCenter: parent.verticalCenter
    width: maxSize
    height: parent.height > minHeight && parent.height < maxSize ? parent.height : maxSize
    visible: enabled && indicatorImage.status === Image.Ready

    property var minHeight: Suru.units.dp(2)
    property var maxSize: Suru.units.dp(12)
    property var bgColor: null
    property var statusMessage: null

    states: [
        State {
            name: "new"
            PropertyChanges {
                target: indicatorImage
                source: Qt.resolvedUrl("qrc:/qml/icons/status/clock-white.svg")
            }
        },
        State {
            name: "outgoing"
            PropertyChanges {
                target: indicatorImage
                source: Qt.resolvedUrl("qrc:/qml/icons/status/clock-white.svg")
            }
        },
        State {
            name: "incoming"
            PropertyChanges {
                target: indicatorImage
                source: ""
            }
        },
        State {
            name: "sent"
            PropertyChanges {
                target: indicatorImage
                source: Qt.resolvedUrl("qrc:/qml/icons/status/check-single-white.svg")
            }
        },
        State {
            name: "read"
            PropertyChanges {
                target: indicatorImage;
                source: Qt.resolvedUrl("qrc:/qml/icons/status/check-double-white.svg")
            }
        }
    ]

    state: {
        if (statusMessage.isOutgoing) {
            if (statusMessage.content.type === QTdObject.MESSAGE_CALL) {
                return "new";
            }

            if (statusMessage.sendingState) {
                return "outgoing";
            }

            if (statusMessage.id > chat.lastReadOutboxMessageId) {
                return "sent";
            }

            return "read";
        }
        return "incoming";
    }

    Image {
        id: indicatorImage
        anchors.fill: parent
        sourceSize: Qt.size(width, height)
        fillMode: Image.PreserveAspectFit
        antialiasing: true
        asynchronous: true
    }

    ColorOverlay {
        anchors.fill: indicatorImage
        source: indicatorImage
        color: Suru.foregroundColor /* if transparent: `messageStatusIndicator.bgColor == "#00000000"` */
    }
}
