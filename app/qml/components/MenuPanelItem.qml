import QtQuick 2.4
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK

MenuItem {
    id: item

    property alias iconName: menu_icon.name
    property alias label: label.text

    height: units.gu(6)
    width: parent.width
        
    UITK.Icon {
        id: menu_icon
        anchors {
            left: parent.left
            leftMargin: units.gu(1)
            verticalCenter: parent.verticalCenter
        }
        width: visible ? units.gu(3) : 0
        height: width
        visible: menu_icon.name != ""
        color: Theme.palette.normal.backgroundSecondaryText
    }

    UITK.Label {
        id: label
        anchors {
            left: menu_icon.visible ? menu_icon.right : parent.left
            leftMargin: units.gu(1)
            verticalCenter: parent.verticalCenter
        }
    }
}
