import QtQuick 2.4
import QuickFlux 1.1
import Lomiri.Connectivity 1.0
import QTelegram 1.0
import "../actions"
import "../components"

Store {
    readonly property alias connectionState: s.connectionState

    Item {
        id: s
        property var connectionState: ConnectionManager.connectionState
    }
    
    Connections {
        target: Connectivity

        Component.onCompleted: {
            ConnectionManager.connectivityOnline = Connectivity.online;
        }

        onOnlineChanged: {
            ConnectionManager.connectivityOnline = Connectivity.online;
        }
    }
}
