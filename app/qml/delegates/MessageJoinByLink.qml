import QtQuick 2.9
import "../actions"

MessageActionItem {
    text: i18n.tr("%1 joined by invite link").arg(
              message.isCollapsed
              ? ""
              : message.sender.fullName).trim()
    onClicked: AppActions.user.showUserInfo(message.sender, null)
}
