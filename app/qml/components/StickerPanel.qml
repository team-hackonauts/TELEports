import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QtQuick.Layouts 1.0
import Lomiri.Components 1.3 as UITK
import "./"
import "../actions"

Item {
    id: sticker_panel

    visible: false

    signal sendStickerRequested(var sticker)
    signal open()
    signal close()

    clip: false
    height: units.gu(24)

    onClose: sticker_panel.visible = false
    onOpen: sticker_panel.visible = true
    onVisibleChanged: {
        if (visible) {
            stickerLoader.load();
            sticker_panel.forceActiveFocus();
        }
    }

    Rectangle {
        id: sticker_box
        anchors.fill: parent
        color: Suru.backgroundColor

        Item {
            anchors.fill: parent

            BusyIndicator {
                anchors.centerIn: parent
                running: stickerLoader.status !== Loader.Ready
            }

            Loader {
                id: stickerLoader

                anchors.fill: parent
                asynchronous: true

                Component {
                    id: stickerSetBoxComponent

                    StickerSetsBox {
                        anchors.fill: parent
                        onSendStickerRequested: {
                            sticker_panel.sendStickerRequested(sticker)
                        }
                    }
                }

                function load() {
                    if (sourceComponent === null) {
                        sourceComponent = stickerSetBoxComponent;
                    }
                }
            }
        }
    }
    Rectangle {
        width: parent.width
        height: Suru.units.dp(1)
        color: Suru.neutralColor
        anchors.bottom: sticker_panel.top
    }
}
