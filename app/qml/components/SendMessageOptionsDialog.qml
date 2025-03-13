import QtQuick 2.9
import QuickFlux 1.1
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QtQuick.Layouts 1.3

import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3
import Lomiri.Components.Pickers 1.3

import QTelegram 1.0
import "../actions"
import "../components"
import "../stores"

PopupDialog {
    property string message
    property string replyId
    property int sendDate: 0
    title: i18n.tr("Send Message options")
    confirmButtonText: i18n.tr("Send")

    RowLayout {
        CheckBox {
            id: pushNotification
            checked: true
        }
        UITK.Label {
            text: i18n.tr("Send push notification")
            wrapMode: Text.Wrap
            Layout.maximumWidth: parent.width - pushNotification.width
        }
    }

    UITK.Label {
        text: i18n.tr("Schedule message:")
    }

    ButtonGroup {
        id: scheduleButtonsGroup
    }
    GridLayout {
        columns: 2
        rows: 4
        width: units.gu(32)
        RadioButton {
            id: deferralNone
            ButtonGroup.group: scheduleButtonsGroup
            checked: true
            onCheckedChanged: if (checked) {
                sendDate = 0;
            }
        }
        UITK.Label {
            text: i18n.tr("Send immediately")
            wrapMode: Text.Wrap
            Layout.maximumWidth: parent.width - deferralNone.width - units.gu(2)
            MouseArea {
                anchors.fill: parent
                onClicked: deferralNone.checked = !deferralNone.checked
            }
        }
        RadioButton {
            id: deferralDateTime
            ButtonGroup.group: scheduleButtonsGroup
        }
        UITK.Label {
            text: i18n.tr("Wait until specified date and time")
            wrapMode: Text.Wrap
            Layout.maximumWidth: parent.width - deferralDateTime.width - units.gu(2)
            MouseArea {
                anchors.fill: parent
                onClicked: deferralDateTime.checked = !deferralDateTime.checked
            }
        }
        RadioButton {
            id: deferralRecipient
            ButtonGroup.group: scheduleButtonsGroup
            onCheckedChanged: if (checked) { sendDate = -1; }
        }
        UITK.Label {
            text: i18n.tr("Wait until the receiver goes online")
            wrapMode: Text.Wrap
            Layout.maximumWidth: parent.width - deferralRecipient.width - units.gu(2)
            MouseArea {
                anchors.fill: parent
                onClicked: deferralRecipient.checked = !deferralRecipient.checked
            }

        }
    }
    AdvancedDateTimePicker {
        id: deferralDateTimeValue
        visible: deferralDateTime.checked
    }
    onConfirmed: {
        if (deferralDateTime.checked) {
            sendDate = Math.round(deferralDateTimeValue.date.getTime() / 1000);
        }
        AppActions.chat.sendMessageWithOptions(message, !pushNotification.checked, sendDate, replyId);
    }

}
