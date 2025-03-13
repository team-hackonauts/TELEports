import QtQuick 2.4
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import QtQuick.Controls.Suru 2.2
import QuickFlux 1.1
import "../actions"

Page {
    id: waitCodePage

    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor

    header: UITK.PageHeader {
        id: header
        title: i18n.tr('Enter your Name')

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
        TextField {
            id: firstNameField
            width: parent.width
            placeholderText: i18n.tr('First Name')
        }

        TextField {
            id: lastNameField
            width: parent.width
            placeholderText: i18n.tr('Last Name')
        }

        Label {
            id: errorLabel
            width: parent.width
            horizontalAlignment: Text.AlignHCenter

            visible: text != ''
            color: "red"
        }
        Button {
            width: parent.width
            text: i18n.tr("Next...")
            onClicked: sendRegistration.run({ firstname: firstNameField.text, lastname: lastNameField.text })
        }
    }

    AppListener {
        Filter {
            type: AuthKey.authRegistrationError
            onDispatched: {
                errorLabel.text = message.error
            }
        }
    }

    AppScript {
       id: sendRegistration
       script: {
           AppActions.auth.registerUser(message.firstname, message.lastname);
            once(AuthKey.authRegistrationError, function(message) {
               exit(1);
           })
           once(AuthKey.authRegistrationAccepted, exit.bind(this,0))
       }
    }
}
