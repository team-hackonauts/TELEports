import QtLocation 5.8
import QtPositioning 5.8
import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QtMultimedia 5.8
import QTelegram 1.0
import QuickFlux 1.1
import QtGraphicalEffects 1.0
import "../actions"
import "../components"

MessageContentBase {
    property QTdMessageLocation location: message.content

    height: Math.max(errorText.height, qtMap.height)
    width: qtMap.width

    Label {
        id: errorText
        anchors.top: parent.top
        text: qtMap.errorString
        visible: qtMap.error != Map.NoError
    }

    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter { name: "osm.mapping.highdpi_tiles"; value: "true" }
    }

    Item {
        anchors.top: parent.top
        Map {
            id: qtMap
            height: maximumAvailableContentWidth * 0.33
            width: maximumAvailableContentWidth * 0.75
            plugin: mapPlugin
            center: QtPositioning.coordinate(location.location.latitude, location.location.longitude)
            zoomLevel: 15
            copyrightsVisible: false
            visible: false
        }
        Rectangle {
            id: mask
            width: qtMap.width
            height: qtMap.height
            visible: false
            border.width: 5
            radius: 4
        }

        OpacityMask {
            anchors.fill: qtMap
            source: qtMap
            maskSource: mask
        }
        UITK.Icon {
            id: background
            width: units.gu(3)
            height: width
            y: qtMap.height / 2 - height
            x: (qtMap.width - width) / 2
            opacity: 0.8
            color: UITK.LomiriColors.ash
            name: "location-active"
        }
        MouseArea {
            anchors.fill: qtMap
            onClicked: {
                Qt.openUrlExternally("geo:" + location.location.latitude + "," + location.location.longitude)
            }
        }
    }


}
