import QtQuick 2.9
import QtQuick.Controls 2.2
import Lomiri.Connectivity 1.0
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.ListItems 1.3 as UITK_ListItem
import Lomiri.Components.Popups 1.3 as UITK_Popups
import QtQuick.Controls.Suru 2.2
import QtQuick.Layouts 1.1
import QTelegram 1.0
import "../actions"
import "../components"
import "../stores"

Page {
    id: connectivityPage

    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor

    property var connectionManager: null
    readonly property var tgConnectionState: connectionManager.connectionState

    property var connectivityStatusMap: [i18n.tr("Offline"), i18n.tr("Connecting"), i18n.tr("Online")]
    property var tgStatusMapText: [
        i18n.tr("Offline"),
        i18n.tr("Connecting To Proxy"),
        i18n.tr("Connecting"),
        i18n.tr("Updating"),
        i18n.tr("Online")
    ]
    property var tgStatusMapImage: ["sync-error", "sync-updating", "sync-updating", "sync-updating", "sync-idle"]

    header: UITK.PageHeader {
        title: i18n.tr('Connectivity')

        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }

        leadingActionBar.actions: [
            BackAction {
                enableShortcut: pageStack.currentItem == connectivityPage
                onTriggered: {
                  AppActions.view.popFromStack()
                }
            }
        ]
    }

    Flickable {
        id: connectivityFlickable
        anchors.fill: parent
        anchors.margins: units.gu(2)
        contentHeight: connectivityColumn.height

        ColumnLayout {
            id: connectivityColumn
            width: parent.width

            UITK.ListItem {
                divider.visible: false
                UITK.ListItemLayout {
                    UITK.Icon {
                        width: units.gu(2)
                        height: width
                        name: tgStatusMapImage[tgConnectionState]
                        UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        color: theme.palette.normal.backgroundSecondaryText
                    }
                    title.text: i18n.tr('Telegram connectivity status:') + ' ' + tgStatusMapText[tgConnectionState]
                }
            }

            UITK.ListItem {
                divider.visible: false
                UITK.ListItemLayout {
                    title.text: i18n.tr("Ubuntu Touch connectivity status:") + " " + connectivityStatusMap[Connectivity.status]
                }
            }

            UITK.ListItem {
                divider.visible: false
                UITK.ListItemLayout {
                    title.text: Connectivity.limitedBandwith ? i18n.tr("Ubuntu Touch bandwith limited") : i18n.tr("Ubuntu Touch bandwith not limited")
                }
            }
        }
    }
}
