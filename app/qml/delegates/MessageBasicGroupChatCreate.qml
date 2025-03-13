import QtQuick 2.9
import "../actions"

MessageActionItem {
    text: message.isChannelPost
            ? i18n.tr("Channel called <b>%1</b> created").arg(content.title)
            : i18n.tr("%1 created a group called <b>%2</b>").arg(getAddingUserString()).arg(content.title).trim()

    onClicked: AppActions.user.showUserInfo(message.sender, null)

    function getAddingUserString() {
        if (message.isCollapsed) {
            return "";
        }
        if(!message.sender) {
            return "";
        }
        
        return message.sender.fullName;
    }
}
