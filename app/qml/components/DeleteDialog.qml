import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import "../actions"

PopupDialog {
    property var message
    property var chat
    property bool isNormalChatOrNormalGroup: !(chat.isSecret || chat.isChannel || chat.isSuperGroup)
    title: i18n.tr("Delete Message")
    text: message.canBeDeletedForAllUsers ?
        (isNormalChatOrNormalGroup ? i18n.tr("Do you really want to delete it?") : i18n.tr("The message will be deleted for all users in the chat. Do you really want to delete it?"))
        : i18n.tr("The message will be deleted only for you. Do you really want to delete it?")
    confirmButtonColor: theme.palette.normal.negative
    confirmButtonText: i18n.tr("Delete")

    Row {
        spacing: 24
        bottomPadding: 24
        visible: message.canBeDeletedForAllUsers && isNormalChatOrNormalGroup

        UITK.CheckBox {
            id: checkBox
            checked: true
        }
        UITK.Label {
            id: label
            text: i18n.tr("Delete for all users")
            MouseArea {
                anchors.fill: parent
                onClicked: checkBox.checked = !checkBox.checked
            }
        }
    }

    onConfirmed: AppActions.chat.deleteMessage(message.id, checkBox.checked)
}
