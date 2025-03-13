import QtQuick 2.9
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import QtQuick.Controls.Suru 2.2
import "../actions"

Page {
    id: secretChatKeyHashPage

    property var keyHashMap: null
    property string keyHashString: ""
    property string userFirstName: ""

    header: UITK.PageHeader {
        title: i18n.tr('Encryption Key')

        leadingActionBar.actions: [
        BackAction {
            enableShortcut: pageStack.currentItem == secretChatKeyHashPage
            onTriggered: {
                AppActions.view.popFromStack()
            }
        }
        ]
    }
    Flickable {
        contentHeight: keyHashCol.height
        anchors.margins: Suru.units.gu(2)
        anchors.fill: parent
        Column {
            id: keyHashCol
            spacing: Suru.units.gu(1)
            width: parent.width
            Column {
                id: hashMap
                width: parent.width
                Repeater {
                    model: keyHashMap
                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        Repeater {
                            model: modelData.hashRow
                            delegate: Rectangle {
                                color: model.hashPixelColor
                                height: Math.min(Suru.units.gu(2), hashMap.width / 12)
                                width: height
                            }
                        }
                    }
                }
            }
            Label {
                id: hashString
                text: keyHashString
                Suru.textLevel: Suru.CodeBlock
                anchors.horizontalCenter: parent.horizontalCenter
            }

            UITK.ListItemLayout {
                id: keyHashSecretChat
                width: parent.width
                padding {
                    top: 0
                    bottom: 0
                }
                title.text: i18n.tr("Check the image or the text. If they match with the ones on <b>%1</b>'s device, end-to-end cryptography is granted.").arg(userFirstName)
                title.maximumLineCount: 7
                title.wrapMode: Text.WordWrap
            }
        }
    }
}
