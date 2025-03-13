import QtQuick 2.9
import QuickFlux 1.1
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3
import "../actions"
import "../components"

PopupDialog {
    property var inviteLinkInfo
    GenericPhoto {
        anchors.horizontalCenter: parent.horizontalCenter
        photoPath: inviteLinkInfo.photo.smallPhotoPath
        initials: inviteLinkInfo.initials
        avatarColor: inviteLinkInfo.avatarColor
        height: Suru.units.gu(10)
        width: height
    }
    UITK.Label {
        textSize: UITK.Label.Large // Suru.textLevel: Suru.HeadingTwo
        anchors.horizontalCenter: parent.horizontalCenter
        text: inviteLinkInfo.title
        horizontalAlignment: Text.AlignHCenter
        width: parent.width
        maximumLineCount: 2
        elide: Text.ElideRight
        wrapMode: Text.Wrap
    }
    UITK.Label {
        opacity: 0.6429 // Suru.textStyle: Suru.TertiaryText
        anchors.horizontalCenter: parent.horizontalCenter
        text: {
            if (inviteLinkInfo.memberCount == inviteLinkInfo.highlightedMemberCount) {
                i18n.tr("%1 member", "%1 members", inviteLinkInfo.memberCount).arg(inviteLinkInfo.memberCount)
            } else {
                i18n.tr("%1 members, among them:").arg(inviteLinkInfo.memberCount)
            }
        }
    }
    Flickable {
        width: Math.min(parent.width, usersRow.width)
        height: usersRow.height
        contentWidth: usersRow.width
        anchors.horizontalCenter: parent.horizontalCenter
        Row {
            id: usersRow
            spacing: Suru.units.gu(2)
            Repeater {
                model: inviteLinkInfo.memberUsers
                delegate: Column {
                    width: Suru.units.gu(8)
                    spacing: Suru.units.gu(0.5)
                    GenericPhoto {
                        anchors.horizontalCenter: parent.horizontalCenter
                        photoPath: modelData.smallPhotoPath
                        initials: modelData.initials
                        avatarColor: modelData.avatarColor(modelData.id)
                        height: Suru.units.gu(6)
                        width: height
                    }
                    UITK.Label {
                        width: parent.width
                        elide: Text.ElideRight
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: modelData.firstName
                        opacity: 0.8571 // Suru.textStyle: Suru.SecondaryText
                    }
                }
            }
        }
    }
    confirmButtonColor: theme.palette.normal.activity
}
