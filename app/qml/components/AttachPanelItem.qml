import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK

Column {
    id: attach_item

    property alias text: attach_label.text
    property alias iconName: attach_icon.name
    signal clicked(var mouse)

    Item {
        width: attach_icon.width
        height: attach_icon.height

        UITK.Icon {
            id: attach_icon
            width: units.gu(4)
            height: width
        }

        MouseArea {
            anchors.fill: parent
            onClicked: attach_item.clicked(mouse)
        }
    }

    Label {
        id: attach_label
        anchors.horizontalCenter: parent.horizontalCenter
        // fontSize: "x-small"
        font.weight: Font.DemiBold
        visible: text != ""
    }
}
