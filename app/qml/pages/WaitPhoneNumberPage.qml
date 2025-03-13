import QtQuick 2.4
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import QtQuick.Controls.Suru 2.2
import QuickFlux 1.1
import "../actions"

Page {
    id: waitPhoneNumberPage

    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor

    header: UITK.PageHeader {
        id: header
        title: i18n.tr("Enter Phone Number")

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
        Button {
            text: i18n.tr("Choose a country")
            width: parent.width
            onClicked: {
                var item = Qt.createComponent("../components/CountryPicker.qml")
                item.createObject(pageStack.currentItem, { })
            }
        }

        Rectangle {
            width: parent.width
            height: countryCodeTextField.height

            TextField {
                id: countryCodeTextField
                width: Suru.units.gu(7)
                text: "+"
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onAccepted: phoneNumberTextField.focus = true
                placeholderText: i18n.tr("Phone number")
                anchors.left: parent.left
            }

            TextField {
                id: phoneNumberTextField
                width: parent.width - countryCodeTextField.width
                text: ""
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onAccepted: setPhoneNumber()
                placeholderText: i18n.tr("Phone number")
                anchors.right: parent.right
            }

            Rectangle {
                anchors.right: phoneNumberTextField.left
                anchors.rightMargin: -width
                anchors.verticalCenter: parent.verticalCenter
                width: Suru.units.gu(0.5)
                height: parent.height - 2
                Rectangle {
                    anchors.centerIn: parent
                    height: parent.height
                    width: 1
                    color: "#CCCCCC" //countryCodeTextField.activeFocus || phoneNumberTextField.activeFocus
                      //? TODO: Find the default color for focus border
                      //: TODO: Find the default color for normal border
                }
            }
        }

        Label {
            width: parent.width
            wrapMode: Text.Wrap
            text: i18n.tr("Please confirm your country code and enter your phone number.")
        }

        Button {
            text: i18n.tr("Manage Proxy Servers...")
            width: parent.width
            onClicked: AppActions.view.pushToStack("qrc:/pages/ProxyManagementPage.qml", { })
        }

        Button {
            text: i18n.tr("Next...")
            width: parent.width
            enabled: countryCodeTextField.text !== "+" && countryCodeTextField.text.slice(0,1) === "+" && phoneNumberTextField.text !== ""
            onClicked: setPhoneNumber()
        }

        Label {
            id: errorLabel
            width: parent.width
            wrapMode: Text.Wrap
            visible: text != ""
            color: Suru.color(Suru.Red)
        }
    }

    function setPhoneNumber () {
        var phoneInput = phoneNumberTextField.displayText.replace(/\D/g,'')
        if ( phoneInput.charAt(0) === "0" ) phoneInput = phoneInput.substr(1)
        phoneInput = countryCodeTextField.text + phoneInput
        sendNumber.run({number: phoneInput})
    }

    AppListener {
        Filter {
            type: AuthKey.authPhoneNumberError
            onDispatched: {
                errorLabel.text = message.error
                phoneNumberTextField.text = ""
            }
        }
    }

    AppScript {
        id: sendNumber
        script: {
            // Enter number including dial code
            AppActions.auth.setPhoneNumber("", message.number);

            once(AuthKey.authPhoneNumberError, function(message) {
                exit(1);
            })

            once(AuthKey.authPhoneNumberAccepted, exit.bind(this,0))
        }
    }
}
