import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QtQuick.Layouts 1.3
import Lomiri.Components 1.3 as Lomiri

Rectangle {
    id: root
    anchors.margins: units.gu(2)
    property string displayText: ""
    property string displaySubText: ""
    property string primaryActionText: ""
    property string secondaryActionText: ""
    property string tertiaryActionText: ""
    property bool closeable: false
    property bool negativeAction: false
    property alias color: root.color
    signal dismissed
    signal primaryActionTriggered
    signal secondaryActionTriggered
    signal tertiaryActionTriggered
    color: theme.palette.normal.activity
    implicitHeight: innerRow.implicitHeight + units.gu(3)
    RowLayout {
        id: innerRow
        anchors.fill: parent
        anchors.leftMargin: units.gu(2)
        anchors.rightMargin: units.gu(2)
        spacing: units.gu(0.5)
        ColumnLayout {
            Lomiri.Label {
                id: toastText
                text: displayText
                color: theme.palette.normal.activityText
                font.pixelSize: units.dp(17)
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                wrapMode: Label.WordWrap
            }
            Lomiri.Label {
                id: toastSubText
                text: displaySubText
                color: theme.palette.normal.activityText
                font.pixelSize: units.dp(15)
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                wrapMode: Label.WordWrap
                visible: displaySubText !== ""
            }
            Row {
                id: buttonRow
                Lomiri.Button {
                    text: primaryActionText
                    color: negativeAction ? theme.palette.normal.negative : theme.palette.normal.positive
                    onClicked: {
                        root.primaryActionTriggered()
                    }
                    visible: primaryActionText !== ""  
                }
                Lomiri.Button {
                    text: secondaryActionText
                    onClicked: {
                        root.secondaryActionTriggered()
                    }                    
                    visible: secondaryActionText !== ""  
                }
                Lomiri.Button {
                    text: tertiaryActionText
                    //color: theme.palette.normal.activity
                    onClicked: {
                        root.tertiaryActionTriggered()
                    }
                    visible: tertiaryActionText !== ""                    
                }
            }
        }
        Lomiri.Icon {
            name: "close"
            color: theme.palette.normal.activityText
            Layout.preferredWidth: units.gu(2.5)
            Layout.preferredHeight: units.gu(2.5)
            Layout.alignment: Qt.AlignVCenter
            visible: closeable
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.dismissed()
                }
            }
        }       
    }
}