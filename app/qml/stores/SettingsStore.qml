import QtQuick 2.4
import QuickFlux 1.1
import Qt.labs.settings 1.0 as Qtlabs
import QTelegram 1.0
import "../actions"

Store {
    readonly property alias theme: s.theme
    readonly property alias uitkTheme: s.uitkTheme
    readonly property alias u1DialogShown: s.onceDialog
    readonly property alias indicators: s.indicators
    readonly property alias citationStackEnabled: s.citationStackEnabled
    readonly property alias proxies: settings.proxies
    Qtlabs.Settings {
        id: s
        property int theme: 2 // 0 = Suru.Light, 1 = Suru.Dark, 2 = Suru.System
        property var uitkTheme: "" // empty string is system theme
        // Dialog shown for U1 account needed for push notifications
        property bool onceDialog: false
        property bool indicators: false
        property bool citationStackEnabled: true
    }

    Settings {
        id: settings

        onProxyManagementError: {
            AppActions.view.showError(i18n.tr("Error"), errorMessage, "");
        }

        onProxyPingError: {
            AppActions.settings.proxyPingError(id, errorMessage);
        }

    }

    Filter {
        type: SettingsKey.setTheme
        onDispatched: {
            s.theme = message.theme != s.theme ? message.theme : s.theme;
            switch(theme) {
                case 0:
                    s.uitkTheme = "Lomiri.Components.Themes.Ambiance";
                    break;
                case 1:
                    s.uitkTheme = "Lomiri.Components.Themes.SuruDark";
                    break;
                case 2:
                    s.uitkTheme = "";
                    break;
            }
        }
    }

    Filter {
        type: SettingsKey.u1dialogShown
        onDispatched: {
            if (!s.onceDialog) {
                s.onceDialog = true
            }
        }
    }

    Filter {
        type: SettingsKey.toggleIndicators
        onDispatched: {
            switch(message.indicators) {
                case true:
                    s.indicators = true;
                    break;
                case false:
                    s.indicators = false;
                    break;
                default:
                    s.indicators = !s.indicators;
            }
        }
    }

    Filter {
        type: SettingsKey.addOrEditProxyServer
        onDispatched: {
            settings.addOrEditProxyServer(message.id, message.server, message.port, message.type, message.username, message.password, message.secret, message.httpOnly, message.enable)
        }
    }
    
    Filter {
        type: SettingsKey.deleteProxyServer
        onDispatched: {
            settings.deleteProxyServer(message.id)
        }
    }
    
    Filter {
        type: SettingsKey.enableProxyServer
        onDispatched: {
            settings.enableProxyServer(message.id)
        }
    }
    
    Filter {
        type: SettingsKey.disableProxyServer
        onDispatched: {
            settings.disableProxyServer()
        }
    }

    Filter {
        type: SettingsKey.fetchProxyServers
        onDispatched: {
            settings.fetchProxyServers()
        }
    }

    Filter {
        type: SettingsKey.setCitationStackEnabled
        onDispatched: {
            s.citationStackEnabled = message.enabled
        }
    }

    // v1.19 had a bug with the initial value. This is here to stay forever I guess, unless we would know that all wrong values
    // have been fixed, which is next to impossible. So lets make this dumb check for eternity
    Component.onCompleted: {
        if (s.uitkTheme === "Lomiri.Components.Themes.System") {
            s.uitkTheme = "";
        }
    }
}
