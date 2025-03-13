import QtQuick 2.9
import "../actions"

MessageActionItem {
    text:  message.isChannelPost
        ? i18n.tr("Channel photo has been removed")
        : i18n.tr("%1 deleted the chat photo").arg(getAddingUserString()).trim()

      function getAddingUserString() {
        if (message.isCollapsed) {
            return "";
        }
        if (!message.sender) {
            return "";
        }

        return message.sender.fullName;
    }
}
