import QtQuick 2.9
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3 as UITK_Popups
import QtQuick.Controls.Suru 2.2
import QtQuick.Layouts 1.1
import QTelegram 1.0
import "../actions"
import "../components"
import "../stores"

Column {
    id: profileColumn
    property bool isSettings: false
    property bool isGroup: false
    property QTdUser user: isSettings ? me : null
    property QTdChat chat: null
    // this component is usually used inside a Flickable which has anchors.margins > 0
    // the margins value is used to extend dividers to full width
    property var parentMargins: 0
    spacing: 0
    RowLayout {
        id: profile
        spacing: Suru.units.gu(1)
        width: parent.width

        GenericPhoto {
            id: avatar
            Layout.preferredHeight: Suru.units.gu(10)
            Layout.preferredWidth: Layout.preferredHeight
            photoPath: isGroup ? chat.chatPhoto.smallPhotoPath : user.smallPhotoPath
            initials: isGroup ? chat.initials : user.initials
            avatarColor: isGroup ? chat.avatarColor(chat.rawId) : user.avatarColor(user.id)
            myself: false
            Layout.alignment: Qt.AlignVCenter
            Component.onCompleted: {
                var bigPhoto = isGroup ? chat.chatPhoto.big : user.profilePhoto.big
                if (bigPhoto.local.canBeDownloaded && !bigPhoto.local.isDownloadingCompleted) {
                    bigPhoto.downloadFile();
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var smallPhoto = isGroup ? chat.chatPhoto.small : user.profilePhoto.small
                    var bigPhoto = isGroup ? chat.chatPhoto.big : user.profilePhoto.big
                    // only test if a photo is available at all, generally no photos are available for generic letter images
                    if (bigPhoto.local.isDownloadingCompleted || smallPhoto.local.isDownloadingCompleted) {
                        // wait for the photo be downloaded? or pass to the PreviewPage the photo object s.t. it can show the photo as soon as the download finished?
                        AppActions.view.pushToStack("qrc:///pages/PreviewPage.qml", {
                            "photoPreviewSource": Qt.resolvedUrl("image://photo/" + (bigPhoto.local.isDownloadingCompleted ? bigPhoto.local.path : smallPhoto.local.path))
                        });
                    }
                }
            }
        }
        Item {
            Layout.preferredHeight: chatTitle.height
            Layout.maximumHeight: avatar.height
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter

            UITK.ListItemLayout {
                id: chatTitle
                anchors.verticalCenter: parent.verticalCenter

                title {
                    text: isGroup ? chat.title : user.fullName
                    font.pixelSize: Suru.units.gu(2.5)
                    wrapMode: Text.Wrap
                    maximumLineCount: 3
                }
                subtitle.text: isGroup ? i18n.tr("Members: %1").arg(parseInt(chat.memberCount)) : user.statusString
                subtitle.font.pixelSize: Suru.units.gu(1.5)
            }
        }
    }

    Item {
        width: parent.width
        height: Suru.units.gu(2)
    }

    Rectangle {
        height: Suru.units.dp(1)
        anchors {
            left: parent.left
            right: parent.right
            leftMargin: -parentMargins
            rightMargin: -parentMargins
        }
        color: Suru.neutralColor
    }
    Column {
        id: profileContent
        anchors {
            left: parent.left
            right: parent.right
        }
        Component.onCompleted: {
            for (var i = children.length - 1; i > -1; i--) {
                if (children[i].visible) {
                    children[i].divider.anchors.leftMargin = -parentMargins
                    children[i].divider.anchors.rightMargin = -parentMargins
                    break
                }
            }
        }
        UITK.ListItem {
            width: parent.width
            height: callUser.height
            visible: isGroup ? false : user.phoneNumber
            UITK.ListItemLayout {
                id: callUser
                UITK.Icon {
                    height: parent.title.font.pixelSize * 2
                    visible: parent.width > Suru.units.gu(20)
                    width: height
                    name: "call-start"
                    UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                }
                title {
                    text: visible ? "<a href='tel:///+"+user.phoneNumber+"'>+" + user.phoneNumber + "</a>" : ""
                    linkColor: Suru.highlightColor
                    onLinkActivated: Qt.openUrlExternally(link)
                }
            }
        }
        UITK.ListItem {
            width: parent.width
            height: chatLink.height
            visible: isGroup ? chat.userName != undefined && chat.userName != ""  : false
            UITK.ListItemLayout {
                id: chatLink
                UITK.Icon {
                    height: parent.title.font.pixelSize * 2
                    visible: parent.width > Suru.units.gu(20)
                    width: height
                    name: "stock_link"
                    UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                }
                title {
                    text: visible ? "https://t.me/" + chat.userName : ""
                    wrapMode: Text.Wrap
                    maximumLineCount: 4
                    elide: Text.ElideRight
                    linkColor: Suru.highlightColor
                    onLinkActivated: Qt.openUrlExternally(link)
                }
                Rectangle {
                    height: parent.title.font.pixelSize * 2.5
                    width: height
                    color: chatLinkCopy.pressed ? Suru.tertiaryForegroundColor : "transparent"
                    UITK.SlotsLayout.position: UITK.SlotsLayout.Trailing
                    MouseArea {
                        id: chatLinkCopy
                        anchors.fill: parent
                        onClicked: UITK.Clipboard.push("https://t.me/" + chat.userName)
                    }
                    UITK.Icon {
                        height: parent.height * 0.6
                        anchors.centerIn: parent
                        width: height
                        name: "edit-copy"
                    }
                }
            }
        }
        UITK.ListItem {
            width: parent.width
            height: inviteLink.height
            visible: isGroup ? chat.inviteLink != "" : false
            UITK.ListItemLayout {
                id: inviteLink
                UITK.Icon {
                    height: parent.title.font.pixelSize * 2
                    visible: parent.width > Suru.units.gu(20)
                    width: height
                    name: "insert-link"
                    UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                }
                title {
                    text: visible ? chat.inviteLink : ""
                    wrapMode: Text.Wrap
                    maximumLineCount: 4
                    elide: Text.ElideRight
                    linkColor: Suru.highlightColor
                    onLinkActivated: Qt.openUrlExternally(link)
                }
                Rectangle {
                    height: parent.title.font.pixelSize * 2.5
                    width: height
                    color: inviteLinkCopy.pressed ? Suru.tertiaryForegroundColor : "transparent"
                    UITK.SlotsLayout.position: UITK.SlotsLayout.Trailing
                    MouseArea {
                        id: inviteLinkCopy
                        anchors.fill: parent
                        onClicked: UITK.Clipboard.push(chat.inviteLink)
                    }
                    UITK.Icon {
                        height: parent.height * 0.6
                        anchors.centerIn: parent
                        width: height
                        name: "edit-copy"
                    }
                }
            }
        }
        UITK.ListItem {
            id: bioListItem
            width: parent.width
            height: descriptionOrBio.height
            property string chatDescription: visible && isGroup ? chat.description : ""
            property string userBio: visible && !isGroup ? user.fullInfo.bio : ""
            property string botBio: visible && !isGroup ? user.fullInfo.shareText : ""
            visible: isGroup ? (chat.description != undefined && chat.description != "") : (user.fullInfo.bio + user.fullInfo.shareText) != ""
            UITK.ListItemLayout {
                id: descriptionOrBio
                UITK.Icon {
                    height: parent.title.font.pixelSize * 2
                    visible: parent.width > Suru.units.gu(20)
                    width: height
                    name: "info"
                    UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                }
                title {
                    text: isGroup ? bioListItem.chatDescription : bioListItem.userBio + bioListItem.botBio
                    wrapMode: Text.Wrap
                    maximumLineCount: 15
                    elide: Text.ElideRight
                    linkColor: Suru.highlightColor
                    onLinkActivated: Qt.openUrlExternally(link) // needs to parse link present in description
                }
            }
        }
        UITK.ListItem {
            width: parent.width
            height: userNameDelegate.height
            visible: isGroup ? false : user.username != ""
            UITK.ListItemLayout {
                id: userNameDelegate
                UITK.Icon {
                    height: parent.title.font.pixelSize * 2
                    visible: parent.width > Suru.units.gu(20)
                    width: height
                    name: "contact"
                    UITK.SlotsLayout.position: UITK.SlotsLayout.Leading
                }
                title.text: visible ? "@" + user.username : ""
                Rectangle {
                    height: parent.title.font.pixelSize * 2.5
                    width: height
                    color: userNameCopy.pressed ? Suru.tertiaryForegroundColor : "transparent"
                    UITK.SlotsLayout.position: UITK.SlotsLayout.Trailing
                    MouseArea {
                        id: userNameCopy
                        anchors.fill: parent
                        onClicked: UITK.Clipboard.push("@" + user.username)
                    }
                    UITK.Icon {
                        anchors.centerIn: parent
                        height: parent.height * 0.6
                        width: height
                        name: "edit-copy"
                    }
                }
            }
        }
    }
}
