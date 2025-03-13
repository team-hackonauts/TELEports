import QtQuick 2.4
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import QtQuick.Layouts 1.3
import QtQuick.Controls.Suru 2.2
import "../../actions"

Page {
    id: addOrEditProxyPage

    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor

    property var proxy: null
    property int id: proxy ? proxy.id : -1
    property string server: proxy ? proxy.server : ""
    property int port: proxy ? proxy.port : -1
    property int type: proxy ? proxy.type.type : -1
    property string username: proxy ? proxy.type.username : ""
    property string password: proxy ? proxy.type.password : ""
    property string secret: proxy ? proxy.type.secret : ""
    property bool httpOnly: proxy ? proxy.type.httpOnly : false
    
    anchors.fill: parent
    header: UITK.PageHeader {
        title: id >= 0 ? i18n.tr("Edit proxy server") : i18n.tr("Add proxy server")
        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }

        leadingActionBar.actions: [
            BackAction {
                enableShortcut: pageStack.currentItem == addOrEditProxyPage
                onTriggered: {
                    AppActions.view.popFromStack()
                }
            }
        ]
        trailingActionBar.actions: [
            UITK.Action {
                iconName: "ok"
                text: i18n.tr('Save')
                visible: serverValue.length > 0 && portValue.length > 0 
                onTriggered: {
                     AppActions.settings.addOrEditProxyServer(id, 
                            serverValue.text,
                            portValue.text,
                            typeValue.currentIndex,
                            usernameValue.text,
                            passwordValue.text,
                            secretValue.text,
                            httpOnly.checked);
                    AppActions.view.popFromStack();
                }
            }
        ]
    }

    function showUsernamePassword() {
        return showHttpOnly() || typeValue.currentIndex === 2;
    }

    function showSecret() {
        return typeValue.currentIndex === 1;
    }

    function showHttpOnly() {
        return typeValue.currentIndex === 0;
    }

    GridLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: units.gu(2)
        columns: 2
        rowSpacing: units.gu(2)
        columnSpacing: units.gu(1)
        UITK.Label {
            text: i18n.tr("Server:")
        }

        UITK.Label {
            Layout.column: 0
            Layout.row: 1
            text: i18n.tr("Port:")
        }
        UITK.Label {
            Layout.column: 0
            Layout.row: 2
            text: i18n.tr("Type:")
        }
        UITK.Label {
            id: usernameLabel
            Layout.column: 0
            Layout.row: 3
            text: i18n.tr("Username:")
            visible: showUsernamePassword()
        }
        UITK.Label {
            Layout.column: 0
            Layout.row: 4
            text: i18n.tr("Password:")
            visible: showUsernamePassword()
        }
        UITK.Label {
            Layout.column: 0
            Layout.row: 5
            text: i18n.tr("Secret:")
            visible: showSecret()
        }
        UITK.Label {
            Layout.column: 0
            Layout.row: 6
            text: i18n.tr("HTTP only:")
            visible: showHttpOnly()
        }
        UITK.TextField {
            Layout.column: 1
            id: serverValue
            text: server
        }
        UITK.TextField {
            Layout.column: 1
            Layout.row: 1
            id: portValue
            text: port
        }
        ComboBox {
            Layout.column: 1
            Layout.row: 2
            id: typeValue
            model: ["HTTP", "MTproto", "SOCKS5"]
            currentIndex: type
        }
        UITK.TextField {
            Layout.column: 1
            Layout.row: 3
            id: usernameValue
            text: username
            visible: showUsernamePassword()
        }
        UITK.TextField {
            Layout.column: 1
            Layout.row: 4
            id: passwordValue
            text: password
            echoMode: TextInput.PasswordEchoOnEdit
            visible: showUsernamePassword()
        }
        UITK.TextField {
            Layout.column: 1
            Layout.row: 5
            id: secretValue
            text: secret
            echoMode: TextInput.PasswordEchoOnEdit
            visible: showSecret()
        }
        UITK.Switch {
            Layout.column: 1
            Layout.row: 6
            id: httpOnlyValue
            checked: httpOnly
            visible: showHttpOnly()
        }
        UITK.Label {
            Layout.column: 0
            Layout.row: 7
            text: i18n.tr("Password:")
            opacity: 0
        }
    }
}