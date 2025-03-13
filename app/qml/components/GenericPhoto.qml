import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QTelegram 1.0

Item {
    property string photoPath: ""
    property string initials: ""
    property string avatarColor: "#000"
    property bool myself: false
    property bool isUser: false
    property bool isOnline: false
    property bool photoExists: photoPath != "" ? true : false

    ShaderEffectSource {
        id: effectSource
        anchors.centerIn: parent
        width: 0
        height: 0
        sourceItem: imageContent
    }

    Item {
        id: imageContent
        anchors.fill: parent
        visible: false

        Rectangle {
            id: bgColorFill
            anchors.fill: parent
            color: myself
                    ? "#65aadd"
                    : photoExists
                        ? photoPath === "image://theme/account"
                            ? Suru.secondaryBackgroundColor
                            : "transparent"
                        : avatarColor
        }

        Image {
            id: itemPicture
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            source: myself ? "qrc:/qml/icons/bookmark.svg" : photoPath
            sourceSize: Qt.size(width, height)
            antialiasing: true
            asynchronous: true
        }

        Rectangle {
            id: onlineMarker
            anchors {
                right: parent.right
                bottom: parent.bottom
                rightMargin: Suru.units.gu(0.4)
                bottomMargin: Suru.units.gu(0.4)
            }
            width: Suru.units.gu(1.25)
            height: width
            color: "springgreen"
            border.color: "white"
            border.width: 1
            radius: width*0.5
            visible: isUser && isOnline
        }
    }

    UITK.Shape {
        id: imgShape
        image: effectSource
        anchors.fill: parent
        aspect: UITK.LomiriShape.DropShadow
        radius: width > Suru.units.gu(7) ? "medium" : "small"
    }

    UITK.Label {
        id: initialsLabel
        anchors.centerIn: parent
        textSize: UITK.Label.Large
        color: photoExists ? "transparent" : "#fff"
        text: initials
        visible: !myself && !photoExists
    }
}
