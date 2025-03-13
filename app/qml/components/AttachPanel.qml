import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import "./"
import "../actions"
Item {
    id: attach_panel

    visible: false

    signal photoRequested()
    signal documentRequested()
    signal videoRequested()
    signal audioRequested()
    signal contactRequested()
    signal locationRequested()
    signal close()

    clip: false

    onClose: attach_panel.visible = false
    height: units.gu(6)

    Rectangle {
        id: attach_box
        anchors.fill: parent
        color: Suru.backgroundColor
        Grid {
            id: attachment_grid
            anchors {
                top: parent.top
                topMargin: units.gu(1)
                horizontalCenter: parent.horizontalCenter
            }
            columns: 7
            rows: 1
            horizontalItemAlignment: Grid.AlignHCenter
            verticalItemAlignment: Grid.AlignVCenter
            spacing: units.gu(1)

            AttachPanelItem {
                id: attach_photo_item
                iconName: "stock_image"
                onClicked: {
                    attach_panel.photoRequested()
                    attach_panel.close()
                }
            }
            AttachPanelItem {
                iconName: "stock_document"
                onClicked: {
                    attach_panel.documentRequested()
                    attach_panel.close()
                }
            }
            AttachPanelItem {
                iconName: "stock_video"
                onClicked: {
                    attach_panel.videoRequested()
                    attach_panel.close()
                }
            }

            AttachPanelItem {
                iconName: "stock_music"
                onClicked: {
                    attach_panel.audioRequested()
                    attach_panel.close()
                }
            }

             AttachPanelItem {
                iconName: "location-active"
                onClicked: {
                    attach_panel.locationRequested()
                    attach_panel.close()
                }
            }

            AttachPanelItem {
                iconName: "stock_contact"
                onClicked: {
                    attach_panel.contactRequested()
                    attach_panel.close()
                }
            }
        }
    }

    Rectangle {
        width: parent.width
        height: Suru.units.dp(1)
        color: Suru.neutralColor
        anchors.bottom: attach_panel.top
    }
}
