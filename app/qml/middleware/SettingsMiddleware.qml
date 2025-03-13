import QtQuick 2.9
import QuickFlux 1.1
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3
import "../actions"
import "../components"

Middleware {
    filterFunctionEnabled: true


    Component {
        id: deleteProxyServerDialog
        PopupDialog {
            text: i18n.tr("Are you sure you want to delete this proxy server?")
            confirmButtonColor: theme.palette.normal.negative
        }
    }

    function openProxyAddDialog() {
        AppActions.view.pushToStack("qrc:/pages/settings/AddOrEditProxyPage.qml", { })
    }

    function openProxyDeleteDialog(id) {
        var dlg = PopupUtils.open(deleteProxyServerDialog, null, {
                        confirmButtonText: i18n.tr("Delete"),
                        })
        dlg.confirmed.connect(function(){
            next(SettingsKey.deleteProxyServer, id)
        })
    }

    function openProxyEditDialog(message) {
        AppActions.view.pushToStack("qrc:/pages/settings/AddOrEditProxyPage.qml", {
                        proxy: message.proxy
                    })
    }

}