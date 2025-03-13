import QtQuick 2.4
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import QtQuick.Controls.Suru 2.2
import "../actions"

Page {
    id: aboutPage
    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor
    header: UITK.PageHeader {
        title: i18n.tr('About')

        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }

        leadingActionBar.actions: [
            BackAction {
                enableShortcut: pageStack.currentItem == aboutPage
                onTriggered: {
                    AppActions.view.popFromStack()
                }
            }
        ]
    }

    Flickable {
        id: aboutFlickable
        anchors.fill: parent
        anchors.topMargin: units.gu(2)
        contentHeight: aboutCloumn.height

        Column {
            id: aboutCloumn
            spacing: units.gu(2)
            width: parent.width

            UITK.LomiriShape {
                width: Suru.units.gu(15)
                height: Suru.units.gu(15)
                radius: "large"
                anchors.horizontalCenter: parent.horizontalCenter
                source: Image {
                    mipmap: true
                    source: "file:///" + applicationDirPath + "/assets/icon.svg"
                }
            }

            Item {
                height: nameAndVersionLayout.height
                width: nameAndVersionLayout.width
                anchors.horizontalCenter: parent.horizontalCenter

                UITK.ListItemLayout {
                    id: nameAndVersionLayout
                    padding {
                        top: units.gu(0)
                        bottom: units.gu(2)
                    }

                    title.text: i18n.tr("Enchnced Teleports")
                    title.font.pixelSize: units.gu(3)
                    title.color: theme.palette.normal.backgroundText
                    title.horizontalAlignment: Text.AlignHCenter

                    subtitle.text: {
                        var versionString = i18n.tr("Version %1").arg(Qt.application.version);
                        if (devBuildHash.length > 0) {
                            versionString = versionString + i18n.tr(" (git# %1)").arg(devBuildHash);
                        }
                        return versionString;
                    }
                    subtitle.color: theme.palette.normal.backgroundTertiaryText
                    subtitle.font.pixelSize: units.gu(1.75)
                    subtitle.horizontalAlignment: Text.AlignHCenter
                }
            }
            Column {
                width: parent.width
                Repeater {
                    id: listViewAbout
                    anchors {
                        left: parent.left
                        right: parent.right
                    }

                    model: [
                        { name: i18n.tr("Get the source"), url: "https://github.com/team-hackonauts/TELEports" },
                        { name: i18n.tr("Report issues"), url: "https://team-hackonauts.github.io/reportisuue/" }
                    ]

                    delegate: UITK.ListItem {
                        UITK.ListItemLayout {
                            title.text : modelData.name
                            UITK.ProgressionSlot {
                                width:units.gu(2)
                            }
                        }
                        onClicked: Qt.openUrlExternally(modelData.url)
                    }
                }
            }
        }
    }
}
