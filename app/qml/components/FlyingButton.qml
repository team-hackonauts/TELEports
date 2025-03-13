import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK

UITK.LomiriShape {

    id: flyingButtonItem
    property var iconName: ""
    signal clicked()
    property var visibleState: false

    width: units.gu(6)
    height: width
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.margins: width / 2
    anchors.rightMargin: -(flyingButtonItem.width * 2)
    property var bgColor: Suru.secondaryBackgroundColor
    backgroundColor: Suru.secondaryBackgroundColor
    aspect: UITK.LomiriShape.DropShadow
    radius: "large"
    opacity: 0.9

    z: 14
    MouseArea {
        id: mouseArea
        onPressed: parent.backgroundColor = Qt.darker(bgColor, 1.3)
        onReleased: parent.backgroundColor = bgColor
        anchors.fill: parent
        enabled: parent.visible
        onClicked: parent.clicked()
    }
    UITK.Icon {
        name: iconName
        width: units.gu(3.5)
        height: width
        anchors.topMargin: height / 2
        anchors.centerIn: parent
        z: 14
        color: theme.palette.normal.baseText
    }

    transitions: Transition {
        SpringAnimation {
            spring: 2
            damping: 0.2
            properties: "anchors.rightMargin"
        }
    }
    states: State {
        name: "visible"
        when: visibleState
        PropertyChanges {
            target: flyingButtonItem
            anchors.rightMargin: flyingButtonItem.width / 2
            backgroundColor: bgColor
        }
    }

}
