import QtQuick 2.9
import "../actions"

MessageActionItem {
    text: message.sender.user && message.sender.id == content.userId
            ? i18n.tr("%1 left the group").arg(getUserString())
            : i18n.tr("%1 removed %2").arg(getRemovingUserString()).arg(getUserString())

    onClicked: AppActions.user.showUserInfo(message.sender, null)

    function getRemovingUserString() {
        if (message.isCollapsed) {
            return "";
        }
        
        return message.sender.fullName;
    }

    function getUserString() {

        if (message.isCollapsed) {
            return ""
        }
          var user = content.user
          if (user.firstName !== "") {
            var fullName = user.firstName
            if (user.lastName !== "")
              fullName = fullName + " " + user.lastName
            return fullName
          } else {
            return user.username
          }
    }
}
