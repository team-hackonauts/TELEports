import QtQuick 2.9
import QuickFlux 1.1
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3
import "../actions"
import "../components"

Middleware {
    filterFunctionEnabled: true

    Component {
        id: confirmationDlg
        PopupDialog {
            confirmButtonColor: theme.palette.normal.negative
        }
    }

    Component {
        id: confirmationDlgWithCheckBox
        PopupDialog {
            id: dialogue
            property var deleteForAllUsers: checkBox.checked
            property var checkBoxText
            Row {
                spacing: 24
                bottomPadding: 24

                UITK.CheckBox {
                    id: checkBox
                    checked: true
                }
                UITK.Label {
                    id: label
                    text: dialogue.checkBoxText
                    MouseArea {
                        anchors.fill: parent
                        onClicked: checkBox.checked = !checkBox.checked
                    }
                }
            }
            confirmButtonColor: theme.palette.normal.negative
        }
    }

    Component {
        id: inviteLinkDialog
        GroupPreviewDialog {}
    }

    Component {
        id: setTTLDialog
        SetTTLDialog {}
    }

    Component {
        id: messageOptionsDlg
        SendMessageOptionsDialog {}
    }

    VCardParser {
        id: contact_parser

        property int importedContactCount: 0
        property string dialogTitle: ""
        property string dialogText: ""

        signal contactsImportedContacts(int importedCount, int retryCount)

        function parseContact(vcardContact) {
            const contact = {};
            contact['phone'] = vcardContact.phoneNumber.number;
            contact['firstName'] = vcardContact.name.firstName;
            contact['lastName'] = vcardContact.name.lastName;
            if (contact['firstName'] === "") {
                const labelName = vcardContact.displayLabel.label.split(" ");
                contact['firstName'] = labelName[0];
                if (labelName.length > 1) {
                    labelName.shift();
                    contact['lastName'] = labelName.toString().replace(",", "");
                } else {
                    contact['lastName'] = "";
                }
            }
            return contact;
        }

        onVcardParsed: {
            if (contacts.length === 0) {
                return;
            }
            for (let i = 0; i < contacts.length; i++) {
                const contact = parseContact(contacts[i]);
                AppActions.chat.sendContactParsed(contact['firstName'], contact['lastName'], contact['phone'], 0);
                importedContactCount++;
            }
        }
    }

    function sendContact(message) {
        contact_parser.vCardUrl = message.url;
    }

    function deleteChatHistory(message) {
        var dlg = PopupUtils.open(confirmationDlgWithCheckBox, root, {
                        title: i18n.tr("Are you sure you want to clear the history?"),
                        confirmButtonText: i18n.tr("Clear history"),
                        checkBoxText: i18n.tr("Delete for all users"),
                        })
        dlg.confirmed.connect(function(){
            message.forAllUsers = dlg.deleteForAllUsers
            next(ChatKey.deleteChatHistory, message)
        })
    }

    function leaveChat(message) {
        var dlg = PopupUtils.open(confirmationDlg, root, {
                        title: i18n.tr("Are you sure you want to leave this chat?"),
                        confirmButtonText: i18n.tr("Leave"),
                        })
        dlg.confirmed.connect(function(){
            next(ChatKey.leaveChat, message)
        })
    }

    function showSendMessageWithOptions(message) {
        var dlg = PopupUtils.open(messageOptionsDlg, root, {
                        message: message.text,
                        replyId: message.replyId
                        })
    }

    function showChatInviteLinkInfo(message) {
        var dlg = PopupUtils.open(inviteLinkDialog, null, {
                        confirmButtonText: i18n.tr("Join group"),
                        inviteLinkInfo: message.info,
                        })
        dlg.confirmed.connect(function(){
            next(ChatKey.joinChatByInviteLink, message)
        })
    }

    function setTTL(message) {
        var dlg = PopupUtils.open(setTTLDialog, root, {secretChat: message.chat})
    }
}
