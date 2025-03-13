import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QTelegram 1.0

Item {
    property bool running: false
    property real percentage: 0.0
    visible: false
    BusyIndicator {
        anchors.fill: parent
        running: parent.running
        UITK.Label {
            anchors.centerIn: parent
            text: percentage.toFixed(0) + "%"
            color: "#e95420"
            style: Text.Outline
            styleColor: Suru.neutralColor
        }
    }
}
