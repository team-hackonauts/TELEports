import QtQuick 2.9
import QuickFlux 1.1
import "./"

ActionCreator {

    signal pushToStack(string view, var properties)
    signal replaceOnStack(string view, var properties)
    signal popFromStack()
    signal popAllButOneFromStack()

    /**
     * Show error in popup dialog
     *
     * title: title of dialog
     * description: description of error
     * callback: the ActionKey to call on closing of the dialog
     */
    signal showError(string title, string description, string callback)

    /**
     * Show error in auto close box
     *
     * text: error text
     */
    signal showAutoCloseNotification(string text)

    /**
     * Show popup dialog to join a private chat
     *
     * info: QTdChatInviteLinkInfo
     */
    signal showChatInviteLinkInfo(var info, string inviteLink)
}
