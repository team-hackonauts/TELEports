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

MessageContentBase
{
    property QTdMessageVideoNote videoNote: message.content
    property QTdLocalFile videoNoteLocal: videoNote.videoNote.video.local
    property QTdThumbnail thumbnail: videoNote.videoNote.thumbnail
    property QTdLocalFile thumbnailLocal: thumbnail.file.local
    property real uniqeId: Math.floor(Math.random() * Math.floor(10000));
    property url localFileSource: videoNote && videoNoteLocal.path ? Qt.resolvedUrl("file://" + videoNoteLocal.path) : ""
    Item {
        id: videoNoteContainer
        width: Suru.units.gu(20)
        height: Suru.units.gu(21)
        Image {
            id: thumbnailImg
            // visible:!media_video.isPlaying
            anchors.fill: parent
            source:videoNote && thumbnailLocal.path? Qt.resolvedUrl("image://photo/" + thumbnailLocal.path) : ""
        }
        Item {
            id: fileIcon
            width: units.gu(7)
            height: units.gu(7)
            anchors.centerIn: parent
            UITK.Icon {
                visible: videoNoteLocal.isDownloadingCompleted
                source: "qrc:/qml/icons/play.svg"
                anchors.fill: parent
            }
            UITK.Icon {
                visible: !videoNoteLocal.isDownloadingCompleted && !videoNoteLocal.isDownloadingActive
                source: "qrc:/qml/icons/download.svg"
                anchors.fill: parent
            }
            BusyPercentageIndicator {
                visible: videoNoteLocal.isDownloadingActive
                anchors.fill: parent
                running: !videoNoteLocal.isDownloadingCompleted
                percentage: parseInt(videoNoteLocal.downloadedSize) / parseInt(videoNote.videoNote.video.size) * 100
            }
        }
        Connections {
            target: videoNote.videoNote.video
            // onFileChanged: {
            //     media_video.reload();
            // }
        }
        Component.onCompleted: {
            if (thumbnailLocal.canBeDownloaded && !thumbnailLocal.isDownloadingCompleted) {
                thumbnail.downloadFile();
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (videoNoteLocal.canBeDownloaded && !videoNoteLocal.isDownloadingCompleted) {
                videoNote.videoNote.video.downloadFile();
            }
            if(videoNoteLocal.isDownloadingCompleted){
                messageContentOpening()
                AppActions.view.pushToStack("qrc:///pages/PreviewPage.qml", {
                                                "fileName": videoNote.videoNote.fileName,
                                                "videoPreviewSource": localFileSource,
                                                "title": message.sender.displayName,
                                                "subtitle": message.formatDate(message.date)
                                            });
            }
        }
    }
}
