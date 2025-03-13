import QtQuick 2.4
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import QtQuick.Controls.Suru 2.2
import QuickFlux 1.1
import "../actions"

Page {
    id: waitPasswordPage

    property string hint
    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor

    header: UITK.PageHeader {
        id: header
        title: i18n.tr("Enter Password")

        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }
    }

    Column {
        width: Math.min(Suru.units.gu(45), parent.width - units.gu(4))
        spacing: Suru.units.gu(2)

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: Suru.units.gu(2)
        }
        UITK.TextField {
            id: passwordField
            width: parent.width
            placeholderText: i18n.tr("Password")
            onAccepted: sendPassword.run({
                password: passwordField.text
            })
            text: ""
            focus: true
            echoMode: TextInput.Password // TODO Change to PasswordEchoOnEdit
        }
        Label {
            id: errorLabel
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            visible: text != ''
            color: "red"
        }

        Label {
            id: hintLabel
            text: i18n.tr("Password hint: %1").arg(hint)
            width: parent.width
        }

        Button {
            text: i18n.tr("Next...")
            width: parent.width
            onClicked: sendPassword.run({
                password: passwordField.text
            })
        }
    }

    AppListener {
        Filter {
            type: AuthKey.authPasswordError
            onDispatched: {
                errorLabel.text = message.error
                passwordField.text = ""
            }
        }
    }

    AppScript {
        id: sendPassword
        script: {
            AppActions.auth.setPassword(message.password);
            once(AuthKey.authPasswordError, function (message) {
                exit(1);
            })
            once(AuthKey.authPasswordAccepted, exit.bind(this, 0))
        }
    }
}
