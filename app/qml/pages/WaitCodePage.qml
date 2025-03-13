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
    property string currentType: ""
    property string nextType: ""
    property int resendTimeout: 0

    header: UITK.PageHeader {
        id: header
        title: i18n.tr('Enter Code')

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
        Label {
            width: parent.width
            wrapMode: Text.Wrap
            text: i18n.tr("A code was sent via Telegram to your other devices.")
            visible: currentType === "authenticationCodeTypeTelegramMessage"
        }
        Label {
            width: parent.width
            wrapMode: Text.Wrap
            text: i18n.tr("A code was sent via text message to your phone.")
            visible: currentType === "authenticationCodeTypeSms"
        }
        Label {
            width: parent.width
            wrapMode: Text.Wrap
            text: i18n.tr("Please enter it here:")
        }
        UITK.TextField {
            id: codeField
            width: parent.width

            placeholderText: i18n.tr('Code')
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            inputMask: "99999"
            maximumLength: 5
            focus: true
            onDisplayTextChanged: {
              if( text.length === maximumLength ) {
                sendCode.run({ code: text })
              }
            }
        }
        Label {
            width: parent.width
            wrapMode: Text.Wrap
            text: i18n.tr("If you do not receive any code after %1 seconds press retry to receive the code via an alternate method").arg(resendTimeout)
            visible: nextType !== ""
        }
        Button {
            id: resendButton
            text: i18n.tr("Resend code...")
            width: parent.width
            onClicked: AppActions.auth.resendCode()
            visible: nextType !== ""
            enabled: false
        }
        Label {
            id: resendInfo
            width: parent.width
            wrapMode: Text.Wrap
            text: i18n.tr("Note: If this is your first signup to Telegram you must register your account via an official mobile App (Android or iOS) first.")
            color: theme.palette.normal.activity
        }

        Label {
            id: errorLabel
            width: parent.width
            horizontalAlignment: Text.AlignHCenter

            visible: text != ''
            color: theme.palette.normal.negative
        }
    }

    Timer {
        interval: resendTimeout
        running: resendTimeout != 0
        repeat: false
        onTriggered: {
            resendButton.enabled = true
            resendInfo.visible = true
        }
    }

    AppListener {
        Filter {
            type: AuthKey.authCodeError
            onDispatched: {
                errorLabel.text = message.error
                if(!message.isLengthWarning)
                    codeField.text = ""
            }
        }
    }

    AppScript {
       id: sendCode
       script: {
           // Enter number including dial code
           AppActions.auth.setCode(message.code);
            once(AuthKey.authCodeError, function(message) {
               exit(1);
           })
           once(AuthKey.authCodeAccepted, exit.bind(this,0))
       }
    }
}
