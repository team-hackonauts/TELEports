pragma Singleton
import QtQuick 2.4
import QuickFlux 1.1

KeyTable {
    property string setTheme
    property string toggleIndicators
    property string setCitationStackEnabled

    /**
     * Callback key to dispatch after prompting
     * about No U1 account during push registration
     */
    property string u1dialogShown

    property string viewConnectivity
    property string viewUserList

    //Proxy management
    property string showProxyManagementPage
    property string addOrEditProxyServer
    property string deleteProxyServer
    property string enableProxyServer
    property string disableProxyServer
    property string fetchProxyServers
    property string openProxyEditDialog
    property string openProxyAddDialog
    property string openProxyDeleteDialog
    property string proxyPingError
}
