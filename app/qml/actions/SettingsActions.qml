import QtQuick 2.4
import QuickFlux 1.1
import "./"

ActionCreator {
    signal setTheme(int theme)
    signal toggleIndicators(bool indicators)
    signal setCitationStackEnabled(bool enabled)

    function viewConnectivity(connectionManager) {
        view.pushToStack("qrc:/pages/ConnectivityPage.qml", {
                         connectionManager: connectionManager
                     })
    }

    function viewUserList() {
        view.pushToStack("qrc:/pages/UserListPage.qml", { })
    }

    //Proxy management
    signal openProxyEditDialog(var proxy)
    signal openProxyAddDialog()
    signal openProxyDeleteDialog(int id)
    signal addOrEditProxyServer(int id, string server, int port, int type, string username, string password, string secret, bool httpOnly)
    signal deleteProxyServer(int id)
    signal enableProxyServer(int id)
    signal disableProxyServer()
    signal fetchProxyServers()
    signal proxyPingError(int id, string error)
    
    function showProxyManagementPage() {
        view.pushToStack("qrc:/pages/ProxyManagementPage.qml", { })
    }

}
