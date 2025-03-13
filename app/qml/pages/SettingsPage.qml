import QtQuick 2.9
import QtQuick.Controls 2.2
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
    id: settingsPage
    property QTdUser me: Telegram.users.me

    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor

    header: UITK.PageHeader {
        title: i18n.tr('Settings')

        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }

        leadingActionBar.actions: [
            BackAction {
                enableShortcut: pageStack.currentItem == settingsPage
                onTriggered: {
                  AppActions.view.popFromStack()
                }
            }
        ]
    }

    Flickable {
        id: settingsFlickable
        anchors.fill: parent
        anchors.margins: units.gu(2)
        contentHeight: settingsColumn.height

        ColumnLayout {
            id: settingsColumn
            width: parent.width
            spacing: 0

            UserProfile {
                Layout.fillWidth: true
                user: me
                parentMargins: settingsFlickable.anchors.margins
                isSettings: true
                UITK.ListItem {
                    width: parent.width
                    height: logOut.height
                    onClicked: UITK_Popups.PopupUtils.open(logoutConfirmationDialog)
                    UITK.ListItemLayout {
                        id: logOut
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "system-log-out"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title.text: i18n.tr('Logout')
                    }
                }
                UITK.ListItem {
                    width: parent.width
                    height: deleteAccount.height
                    onClicked: UITK_Popups.PopupUtils.open(deleteAccountConfirmationDialog)
                    UITK.ListItemLayout {
                        id: deleteAccount
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "delete"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title.text: i18n.tr("Delete account")
                    }
                }
                UITK.ListItem {
                    width: parent.width
                    height: proxyManagement.height
                    onClicked: AppActions.view.pushToStack("qrc:/pages/ProxyManagementPage.qml", { })
                    UITK.ListItemLayout {
                        id: proxyManagement
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "stock_website"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title.text: i18n.tr("Proxy Management")
                    }
                }
                UITK.ListItem {
                    width: parent.width
                    height: connectivityStatus.height
                    onClicked: AppActions.view.pushToStack("qrc:/pages/ConnectivityPage.qml", {connectionManager: Telegram.connections})
                    UITK.ListItemLayout {
                        id: connectivityStatus
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "info"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title.text: i18n.tr("Connectivity status")
                    }
                }
                UITK.ListItem {
                    width: parent.width
                    height: indicatorsDelegate.height
                    onClicked: switchDelegate.checked = !switchDelegate.checked
                    UITK.ListItemLayout {
                        id: indicatorsDelegate
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "preferences-desktop-accessibility-symbolic"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title {
                            text: i18n.tr('Toggle message status indicators')
                            wrapMode: Text.Wrap
                            maximumLineCount: 3
                            elide: Text.ElideRight
                        }
                        UITK.Switch {
                            id: switchDelegate
                            checked: Telegram.settingsStore.indicators
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Trailing
                            onCheckedChanged: AppActions.settings.toggleIndicators(checked)
                        }
                    }
                }
                UITK.ListItem {
                    width: parent.width
                    height: citationStackEnabledItem.height
                    onClicked: citationStackEnabledSwitch.checked = !citationStackEnabledSwitch.checked
                    UITK.ListItemLayout {
                        id: citationStackEnabledItem
                        UITK.Icon {
                            height: parent.title.font.pixelSize * 2
                            visible: parent.width > Suru.units.gu(20)
                            width: height
                            name: "mail-reply"
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                        }
                        title {
                            text: i18n.tr("Navigate through replied messages")
                            wrapMode: Text.Wrap
                            maximumLineCount: 3
                            elide: Text.ElideRight
                        }
                        UITK.Switch {
                            id: citationStackEnabledSwitch
                            checked: Telegram.settingsStore.citationStackEnabled
                            UITK.SlotsLayout.position: UITK.SlotsLayout.Trailing
                            onCheckedChanged: AppActions.settings.setCitationStackEnabled(checked)
                        }
                    }
                }
            }
        }
    }

    Component {
        id: logoutConfirmationDialog
        PopupDialog {
            text: i18n.tr("Warning: Logging out will delete all local data from this device, including secret chats. Are you still sure you want to log out?")
            confirmButtonColor: theme.palette.normal.negative
            confirmButtonText: i18n.tr("Logout")
            onConfirmed: AppActions.auth.logOut()
        }
    }

    Component {
        id: deleteAccountConfirmationDialog
        PopupDialog {
            text: i18n.tr("Warning: Deleting the account will delete all the data you ever received or sent using telegram except for data you have explicitly saved outside the telegram cloud. Are you really really sure you want to delete your telegram account?")
            confirmButtonColor: theme.palette.normal.negative
            confirmButtonText: i18n.tr("Delete")
            onConfirmed: AppActions.auth.deleteAccount()
        }
    }
}
