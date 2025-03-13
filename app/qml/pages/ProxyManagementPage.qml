import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3 as UITK_Popups
import QuickFlux 1.1
import QTelegram 1.0
import "../components"
import "../actions"
import "../stores"

Page {
    id: proxyManagementPage
    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor
    header: UITK.PageHeader {
        title: i18n.tr("Proxy Management")

        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }

        leadingActionBar.actions: [
            BackAction {
                enableShortcut: pageStack.currentItem == proxyManagementPage
                onTriggered: {
                    AppActions.view.popFromStack()
                }
            }
        ]
        trailingActionBar.actions: [
            UITK.Action {
                iconName: "add"
                text: i18n.tr('Add proxy server')
                onTriggered: {
                    AppActions.settings.openProxyAddDialog()
                    }
            }
        ]
    }

    ColumnLayout {
        anchors.fill: parent
        // UITK.SlotsLayout {
        //     id: headerSlots
        //     mainSlot: UITK.Label {
        //         Layout.fillWidth: true
        //         text: i18n.tr("Use a proxy server to connect to Telegram")
        //         wrapMode: Label.WordWrap
        //     }
        //     Switch {
        //         id: enableSwitch
        //         UITK.SlotsLayout.position: UITK.SlotsLayout.Trailing
        //         Suru.highlightType: Suru.PositiveHighlight
        //         checked: Telegram.settingsStore.indicators
        //         onToggled: checked? AppActions.settings.enableProxyServer(proxy.rawId) : AppActions.settings.disableProxyServer(proxy.rawId)
        //     }
        // }
        ListView {
        id: proxyServerList
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: Telegram.settingsStore.proxies
            delegate: UITK.ListItem {
                readonly property QTdProxy proxy: modelData
                width: proxyServerList.width
                height: mainLayout.height
                color: "transparent"

                leadingActions: UITK.ListItemActions {
                    actions: [
                        UITK.Action {
                            iconName: "edit-clear"
                            text: i18n.tr("Delete")
                            onTriggered: AppActions.settings.openProxyDeleteDialog(proxy.rawId)
                        }
                    ]
                }
                trailingActions: UITK.ListItemActions {
                    actions: [
                        UITK.Action {
                            iconName: "edit"
                            text: i18n.tr("Edit")
                            onTriggered: AppActions.settings.openProxyEditDialog(proxy)
                        }
                    ]
                }

                UITK.SlotsLayout {
                    id: mainLayout
                    mainSlot: ColumnLayout {
                        width: parent.width
                        UITK.Label {
                            id: server
                            elide: Text.ElideRight
                            wrapMode: Text.WrapAnywhere
                            maximumLineCount: 1
                            font.weight: Font.DemiBold
                            font.pixelSize: units.dp(17)
                            text: proxy.server
                            Layout.fillWidth: true
                        }
                        UITK.Label {
                            Layout.preferredWidth: width
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                            wrapMode: Label.WordWrap
                            maximumLineCount: 1
                            font.pixelSize: units.dp(15)
                            Suru.textStyle: Suru.TertiaryText
                            text: i18n.tr("Port: %1 Type: %2 Ping: %3ms").arg(proxy.port).arg(proxy.type.typeString).arg(proxy.ping > -1 ? proxy.ping.toFixed(0) : "???")
                        }
                        UITK.Label {
                            id: proxyPingError
                            Layout.preferredWidth: width
                            Layout.fillWidth: true
                            font.pixelSize: units.dp(15)
                            Suru.textStyle: Suru.TertiaryText
                            wrapMode: Label.WordWrap
                            visible: text != ""
                            color: theme.palette.normal.negative
                        }
                    }
                    Switch {
                        id: enableSwitch
                        UITK.SlotsLayout.position: UITK.SlotsLayout.Trailing
                        Suru.highlightType: Suru.PositiveHighlight
                        checked: proxy.isEnabled
                        enabled: proxy.ping > -1
                        onToggled: proxy.isEnabled ? AppActions.settings.disableProxyServer(proxy.rawId) : AppActions.settings.enableProxyServer(proxy.rawId)
                    }
                }
                
                AppListener {
                    Filter {
                        type: SettingsKey.proxyPingError
                        onDispatched: {
                            if (message.id == proxy.id) {
                                proxyPingError.text = message.error
                            }
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        AppActions.settings.fetchProxyServers()
    }
}