import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QtMultimedia 5.8
import QTelegram 1.0
import QuickFlux 1.1
import "../actions"
import "../components"

MessageContentBase {
    property QTdMessageAnimation animation: message.content
    property QTdLocalFile animationLocal: animation.animation.animation.local
    property QTdThumbnail thumbnail: animation.animation.thumbnail
    property QTdMiniThumbnail miniThumbnail: animation.animation.miniThumbnail
    property QTdLocalFile thumbnailLocal: thumbnail.file.local
    property real uniqeId: Math.floor(Math.random() * Math.floor(10000));
    property real maximumMediaHeight: Suru.units.gu(24)
    property real minimumMediaHeight: Suru.units.gu(16)
    property real maximumMediaWidth: Suru.units.gu(30)
    property real maximumMediaRatio: maximumMediaWidth / maximumMediaHeight
    property real mediaWidth:animation.animation.width
    property real mediaHeight:animation.animation.height
    property url localFileSource: animation && animationLocal.path ? Qt.resolvedUrl("file://" + animationLocal.path) : ""

    Item {
        id: animationContainer
        width: mediaWidth > mediaHeight?
                   Math.min(mediaWidth, maximumMediaWidth):
                   mediaWidth * Math.min(1, maximumMediaHeight / mediaHeight)
        height: mediaHeight >= mediaWidth?
                    Math.max(fileIcon.height, Math.min(mediaHeight, maximumMediaHeight)):
                    Math.max(mediaHeight * Math.min(1, maximumMediaWidth / mediaWidth), minimumMediaHeight)

        Image {
            id: thumbnailImg
            anchors.fill: parent
            source: animation
                && thumbnail.format
                && thumbnail.format.type !== QTdObject.THUMBNAIL_FORMAT_MPEG4
                    ? thumbnailLocal.path ? Qt.resolvedUrl("image://photo/" + thumbnailLocal.path) : ""
                    : miniThumbnail.dataURL
        }

        Item {
            id: fileIcon
            width: units.gu(7)
            height: units.gu(7)
            anchors.centerIn: parent
            UITK.Icon {
                visible: animationLocal.isDownloadingCompleted
                source: "qrc:/qml/icons/play.svg"
                anchors.fill: parent
            }
            UITK.Icon {
                visible: !animationLocal.isDownloadingCompleted && !animationLocal.isDownloadingActive
                source: "qrc:/qml/icons/download.svg"
                anchors.fill: parent
            }
            BusyPercentageIndicator {
                visible: animationLocal.isDownloadingActive
                anchors.fill: parent
                running: !animationLocal.isDownloadingCompleted
                percentage: parseInt(animationLocal.downloadedSize) / parseInt(animation.animation.animation.size) * 100
            }
        }

        Connections {
            target: animation.animation.animation
            onFileChanged: {
                // media_video.reload();
            }
        }
        Component.onCompleted: {
            if (thumbnailLocal.canBeDownloaded && !thumbnailLocal.isDownloadingCompleted) {
                thumbnail.downloadFile();
            }
        }
    }

    FormattedText {
        anchors {
            top: animationContainer.bottom
            topMargin: message.isOutgoing ? Suru.units.dp(10) : Suru.units.dp(5)
        }

        isPreview: message.isCollapsed
        maximumWidth: maximumAvailableContentWidth
        formattedText: animation.caption
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (animationLocal.canBeDownloaded && !animationLocal.isDownloadingCompleted) {
                animation.animation.animation.downloadFile();
            }
            if(animationLocal.isDownloadingCompleted){
                messageContentOpening()
                AppActions.view.pushToStack("qrc:///pages/PreviewPage.qml", {
                                                "fileName": animation.animation.fileName,
                                                "videoPreviewSource": localFileSource,
                                                "title": message.sender.displayName,
                                                "subtitle": message.formatDate(message.date)
                                            })
            }
        }
    }
}
