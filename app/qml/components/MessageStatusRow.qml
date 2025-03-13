import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK

Row {
    id: message_status_row
    spacing: units.dp(4)
    opacity: message && message.isOutgoing ? 1 : 0.8
    property var textStyle: Suru.TertiaryText

    Row {
        id: channel_views
        visible: message && message.views !== ""
        anchors.verticalCenter: parent.verticalCenter
        UITK.Icon {
            anchors.verticalCenter: parent.verticalCenter
            width: units.gu(2)
            height: width
            source: Qt.resolvedUrl("qrc:/qml/icons/eye.svg")
            color: channel_views_count.color
        }

        Label {
            id: channel_views_count
            anchors.verticalCenter: parent.verticalCenter
            text: message ? message.views : ''
            Suru.textLevel: Suru.Small
            Suru.textStyle: textStyle
        }
    }

    Label {
        anchors.verticalCenter: parent.verticalCenter
        id: editedLabel
        text: i18n.tr("Edited")
        visible: message && message.isEdited
        Suru.textLevel: Suru.Small
        Suru.textStyle: textStyle
    }

    Label {
        id: dateLabel
        text: message ? message.formatDate(message.date) : ''
        anchors.verticalCenter: parent.verticalCenter
        Suru.textLevel: Suru.Small
        Suru.textStyle: textStyle
    }
}
