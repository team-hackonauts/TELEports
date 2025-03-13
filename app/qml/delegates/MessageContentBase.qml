import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QTelegram 1.0

import "../components"
import "../stores"
import "../actions"

Item {
    id: content

    default property alias content: mainContent.data
    property real contentLoaderWidth: Math.max(citationLoader.width, forwardLoader.width) 
    property QTdMessage message: null
    property bool contentBeforeMain: forwardLoader.active || citationLoader.active

    signal messageContentOpening()

    width: Math.max(implicitWidth, contentColumn.width)
    height: contentColumn.height + contentColumn.anchors.topMargin

    Component {
        id: citation
        Citation {
            messageCited: message.messageRepliedTo
        }
    }
    Component {
        id: forward
        Item {
            height: childrenRect.height
            width: multimediaLayout || mcMargins == 0 ? mainContent.width-2*anchors.leftMargin : Math.min(maximumAvailableContentWidth, childrenRect.width)
            anchors {
                leftMargin: mcMargins == 0 && !message.isCollapsed ? Suru.units.dp(5) : 0
                left: parent.left
            }
            Label {
                text: i18n.tr("Forwarded from %1").arg(message.forwardInfo.displayedName)
                color: "#FF335280" //Suru.Blue
                font.weight: Font.Medium
                wrapMode: Text.WrapAnywhere
                elide: Text.ElideRight
                maximumLineCount: 2
                width: multimediaLayout || mcMargins == 0 ? mainContent.width-2*parent.anchors.leftMargin : implicitWidth
                height: implicitHeight
            }
        }
    }

    // Ensure that the message replied to is loaded always
    // Not sure why we have to do that... Thanks to @TimDev for the hint!
    Connections {
        target: message
        onMessageRepliedToChanged: {
            citationLoader.sourceComponent = null
            citationLoader.sourceComponent = citation
        }
        onHighlight: {
            highlight();
        }
    }

    Column {
        id: contentColumn
        spacing: Suru.units.dp(5)
        anchors {
            topMargin: (forwardLoader.active || citationLoader.active) && mcMargins == 0 && !message.isCollapsed ? Suru.units.dp(5) : 0
            top: parent.top
        }

        width: Math.max(citationLoader.width, mainContent.width, forwardLoader.width)
        Loader {
            id: forwardLoader
            active: message && message.isForwarded && !message.isReply
            asynchronous: true
            sourceComponent: forward
        }

        // Show an icon on the right to expand/collapse the citation?
        Loader {
            id: citationLoader
            active: message && message.isReply && !message.isCollapsed
            asynchronous: true
            sourceComponent: citation
            anchors {
                leftMargin: mcMargins == 0 ? Suru.units.dp(5) : 0
                left: parent.left
            }
        }

        Item {
            id: mainContent
            height: childrenRect.height
            implicitWidth: Math.max(childrenRect.width, content.implicitWidth)
        }
    }

    onMessageContentOpening: {
        AppActions.chat.openMessageContent(message.chatId, message.id)
    }
}
