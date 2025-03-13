import QtQuick 2.9
import "../actions"

MessageActionItem {
    text: i18n.tr("%1 has joined Telegram!").arg(getAddingUserString()).trim()

    function getAddingUserString() {
        if (message.isCollapsed) {
            return "";
        }

        return message.sender.fullName;
    }
}
