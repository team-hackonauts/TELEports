import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QTelegram 1.0
import Lomiri.Components 1.3 as UITK

Item {
    id: editBox

    property bool enabled
    property string title
    property bool editing: false
    property var message
    readonly property string text: message ? message.content.infoText : ""
    readonly property string typeText: message ? message.content.typeText : ""
    readonly property var imgUrl: message ? message.content.infoImageUrl : ""

    signal closeRequested()

    height: units.gu(7)
    clip: true

    MouseArea {
        // only for blocking mouse and touch events
        anchors.fill: parent
        enabled: editBox.enabled
    }

    Rectangle {
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            topMargin: editBox.enabled ? 0 : height
        }

        visible: anchors.topMargin != height
        height: parent.height
        color: Suru.backgroundColor

        Rectangle {
            anchors {
                top: parent.top
                right: parent.right
                left: parent.left
            }
            height: Suru.units.dp(1)
            color: Suru.neutralColor
        }

        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: Suru.units.gu(2)
            anchors.leftMargin: Suru.units.gu(2)
            anchors.margins: Suru.units.gu(1)

            spacing: units.gu(1)

            AbstractButton {    //without the AbstractButton the Icon does not work. it doesn't need to handle click events
                Layout.fillHeight: true
                implicitWidth: Suru.units.gu(3)
                UITK.Icon {
                    anchors.centerIn: parent
                    id: icon_left
                    name: editing ? "edit" : "mail-reply"
                    color: Suru.color(Suru.theme == Suru.Dark ? Suru.Porcelain : Suru.Blue)
                    width: units.gu(3)
                    height: width
                }
            }

            UITK.LomiriShape {
                Layout.maximumWidth: units.gu(5)
                Layout.maximumHeight: units.gu(5)
                visible: imgUrl != ""
                aspect: UITK.LomiriShape.Flat
                sourceFillMode: UITK.LomiriShape.PreserveAspectCrop
                source: Image {
                    asynchronous: true
                    source: imgUrl != "" ? imgUrl: ""
                }
            }

            Column {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
                spacing: units.dp(4)

                Label {
                    text: editing ? i18n.tr("Edit message") : message ? message.sender.fullName : ""
                    font.bold: true
                    color: Suru.color(Suru.Blue)
                }

                RowLayout {
                    width: parent.width
                    spacing: Suru.units.dp(4)
                    Label {
                        id: msgTypeLabel
                        visible: text != ""
                        text: typeText
                        Suru.textStyle: Suru.TertiaryText
                        Layout.preferredWidth: implicitWidth
                        Layout.maximumWidth: parent.width
                        wrapMode: Text.NoWrap
                        elide: Text.ElideRight
                        maximumLineCount: 1
                    }
                    Label {
                        id: captionLabel
                        Layout.fillWidth: true
                        text: editBox.text
                        wrapMode: Text.NoWrap
                        elide: Text.ElideRight
                        maximumLineCount: 1
                    }
                }
            }

            AbstractButton {
                Layout.fillHeight: true
                implicitWidth: Suru.units.gu(3)

                UITK.Icon {
                    anchors.centerIn: parent
                    name: "close"
                    color: Suru.foregroundColor
                    width: units.gu(3)
                    height: width
                }

                onClicked: closeRequested()
            }
        }

        Behavior on anchors.topMargin {
            NumberAnimation {
                duration: 100
                easing.type: Easing.InQuad
            }
        }
    }
}
