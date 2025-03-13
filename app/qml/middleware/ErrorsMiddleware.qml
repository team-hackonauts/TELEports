import QtQuick 2.9
import QuickFlux 1.1
import Lomiri.Components 1.3
import Lomiri.Components.Popups 1.3
import "../actions"

Middleware {
    filterFunctionEnabled: true

    Component {
        id: errorDlg

        Dialog {
            id: dlg
            property string callback

            Button {
                width: parent.width
                text: i18n.tr("Close")
                onClicked: {
                    if (callback !== "") {
                        next(dlg.callback)
                    }
                    PopupUtils.close(dlg)
                }
            }
        }
    }

    function showError(message) {
        PopupUtils.open(errorDlg, root, {
                        title: message.title,
                        text: message.description,
                        callback: message.callback ? message.callback : ""
                        })
    }
}
