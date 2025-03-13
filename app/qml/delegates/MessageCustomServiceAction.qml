import QtQuick 2.9
import "../actions"

MessageActionItem {
    text: "%1 %2".arg(getAddingUserString()).arg(content.text).trim()

    function getAddingUserString() {
        if (message.isCollapsed) {
            return "";
        }
        
        return message.sender.fullName;
    }
}
