import QtQuick 2.9
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QTelegram 1.0
import Lomiri.Components 1.3 as UITK
import QuickFlux 1.1
import "../actions"

Item {
    id: keyboard

    property QtObject replyMarkup
    property QtObject rows: replyMarkup.rows
    property bool resizeKeyboard: replyMarkup.resizeKeyboard
    property bool oneTime: replyMarkup.oneTime  //TODO
    property bool isPersonal: replyMarkup.isPersonal    //TODO

    property var kHeight: root.height * (root.landscape ? root.tablet ? 0.34 : 0.49
                                                        : root.tablet ? 0.31 : 0.40)
                                      + (root.tablet ? Suru.units.gu(6) : Suru.units.gu(4))
    property bool hidden: false
    visible: !hidden
    height: resizeKeyboard ? Math.min(kHeight, colLayout.height+Suru.units.gu(1)) : kHeight
    anchors {
        bottomMargin: (hidden || LomiriApplication.inputMethod.visible) ? -height : 0
        onBottomMarginChanged: hidden = (anchors.bottomMargin==-height ? true : hidden)

        Behavior on bottomMargin {
            NumberAnimation {
                duration: UITK.LomiriAnimation.FastDuration
                easing: UITK.LomiriAnimation.StandardEasing
            }
        }
    }

    Rectangle {
        color: Suru.backgroundColor
        anchors.fill: parent

        ScrollView {
            anchors.fill: parent
            contentHeight: colLayout.height + Suru.units.gu(1)
            contentWidth: width
            clip: true

            ColumnLayout {
                id: colLayout
                width: parent.width
                height: resizeKeyboard ? implicitHeight : Math.max(implicitHeight, kHeight - Suru.units.gu(1))

                Repeater {
                    model: rows ? rows : null

                    RowLayout {
                        Layout.leftMargin: Suru.units.gu(1)
                        Layout.rightMargin: Suru.units.gu(1)

                        Repeater {
                            model: modelData.row
                            delegate: Button {
                                Layout.fillWidth: true
                                Layout.fillHeight: !resizeKeyboard
                                Layout.minimumHeight: implicitHeight
                                text: model.text
                                onClicked: {
                                    AppActions.chat.sendMessage(text.trim())
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
