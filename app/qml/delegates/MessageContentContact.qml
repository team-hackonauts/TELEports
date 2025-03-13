import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QuickFlux 1.1
import QTelegram 1.0
import "../components"
import "../actions"
import "../delegates"
import "../stores"

MessageContentBase {
    id: item

    property QTdContact contact: message.content.contact
    property QTdUser user: contact.user

    width: Math.max(maximumAvailableContentWidth / 2, renderedContact.width)

    RowLayout {
        id: renderedContact

        GenericPhoto {
            id: avatar
            height: units.gu(8)
            width: height
            photoPath: user ? user.smallPhotoPath : ""
            avatarColor: user ? user.avatarColor(user.id) : "#65aadd"
            initials: user ? user.initials : contact.initials
            myself: false
        }        
        ColumnLayout {
            UITK.Label {
                Layout.fillWidth: true
                text: "<b>%1 %2</b>".arg(contact.firstName).arg(contact.lastName)
                color: Suru.foregroundColor
            }

            RowLayout {
                visible: contact.phoneNumber != ""
                UITK.Icon {
                    height: units.gu(2)
                    width: height
                    name: "call-start"
                }
                UITK.Label {
                    text: "<a href='tel:///"+contact.phoneNumber+"'>" + contact.phoneNumber + "</a>"
                }
            }

            RowLayout {
                visible: user && user.username != ""
                UITK.Icon {
                    height: units.gu(2)
                    width: height
                    name: "contact"
                }
                UITK.Label {
                    text: user ? "@" + user.username : ""
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        enabled: user || contact.phoneNumber != ""
        onClicked: {
            if (user) {
                AppActions.user.showUserInfo(user, currentChat);
            } else if (contact.phoneNumber != "") {
                Qt.openUrlExternally("tel:///" + contact.phoneNumber);
            }
        }
    }
}

