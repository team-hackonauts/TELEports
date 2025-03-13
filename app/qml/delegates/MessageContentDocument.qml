import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QtMultimedia 5.8
import QTelegram 1.0
import QuickFlux 1.1
import Lomiri.Content 1.1
import "../actions"
import "../components"

MessageContentBase {
    property QTdMessageDocument documentContent: message.content
    property QTdFile tdFile: documentContent.document.document
    property QTdLocalFile localFile: tdFile.local
    property QTdRemoteFile remoteFile: tdFile.remote
    property QTdThumbnail thumbnail: documentContent.document.thumbnail
    property QTdLocalFile thumbnailLocal: thumbnail.file.local ? thumbnail.file.local : null
    property url localFileSource: tdFile && localFile.path ? Qt.resolvedUrl("file://" + localFile.path) : ""
    property url photoFileSource: tdFile && localFile.path ? Qt.resolvedUrl("image://photo/" + localFile.path) : ""
    property url thumbnailLocalSource: thumbnail && thumbnailLocal.path ? Qt.resolvedUrl("image://photo/" + thumbnailLocal.path) : ""

    Item {
        id: documentContainer
        width: maximumAvailableContentWidth
        // width:  documentIcon.width+fileNameLabel.width+Suru.units.gu(2))
        height:Math.max(fileNameLabel.height,fileIcon.height)

        Component.onCompleted: {
            if (thumbnailLocal && thumbnailLocal.canBeDownloaded && !thumbnailLocal.isDownloadingCompleted) {
                thumbnail.downloadFile();
            }
        }
        UITK.LomiriShape {
            id: thumbnailBg
            visible: thumbnailLocalSource != ""
            anchors.fill: fileIcon
            source: Image { source: thumbnailLocalSource }
            sourceFillMode: UITK.LomiriShape.PreserveAspectCrop
        }
        Item {
            id: fileIcon
            width: units.gu(7)
            height: units.gu(7)
            anchors.rightMargin: Suru.units.gu(2)
            Item {
                id: overlay_content
                width: parent.width * 0.64
                height: width
                anchors.centerIn: parent
            }
            UITK.Icon {
                visible: localFile.isDownloadingCompleted && !thumbnailBg.visible
                color: UITK.LomiriColors.ash
                name: "document-open"
                anchors.fill: parent
            }
            Rectangle {
                id: circle_overlay
                radius: width / 2
                color: UITK.LomiriColors.porcelain
                opacity: 0.5
                width: parent.width * 0.8
                height: width
                visible: (percentage_spinner.visible || download_icon.visible) && thumbnailBg.visible
                anchors.centerIn: parent
            }
            UITK.Icon {
                id: download_icon
                visible: !localFile.isDownloadingCompleted && !localFile.isDownloadingActive
                source: "qrc:/qml/icons/download.svg"
                anchors.fill: thumbnailBg.visible ? overlay_content : parent
                color: UITK.LomiriColors.inkstone
            }
            BusyPercentageIndicator {
                id: percentage_spinner
                anchors.fill: thumbnailBg.visible ? overlay_content : parent
                visible: localFile.isDownloadingActive || remoteFile.isUploadingActive
                running: !localFile.isDownloadingCompleted || !remoteFile.isUploadingCompleted
                percentage: {
                    if (localFile.isDownloadingActive) {
                        return parseInt(localFile.downloadedSize) / parseInt(tdFile.size) * 100;
                    } else if (remoteFile.isUploadingActive) {
                        return parseInt(remoteFile.uploadedSize) / parseInt(tdFile.size) * 100;
                    }
                    return 0.0;
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (localFile.canBeDownloaded && !localFile.isDownloadingCompleted) {
                        tdFile.downloadFile();
                    }
                    if(localFile.isDownloadingCompleted){
                        messageContentOpening();
                        if (documentContent.document.mimeType.includes("image")) {
                            AppActions.view.pushToStack("qrc:///pages/PreviewPage.qml", {
                                                            "photoPreviewSource": photoFileSource,
                                                        "title": message.sender.displayName,
                                                        "subtitle": message.formatDate(message.date)
                                                        });
                        } else {
                            AppActions.view.pushToStack("qrc:///pages/PickerPage.qml", {
                                                            "contentUrl": localFileSource,
                                                            "handler": ContentHandler.Destination,
                                                            "contentType": ContentType.Documents
                                                        });
                        }
                    }
                }
            }
        }
        Label {
            id: fileNameLabel
            height: contentHeight
            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
            anchors{
                left: fileIcon.right
                right: parent.right
                top: parent.top
                leftMargin: Suru.units.gu(2)
            }
            text: documentContent.document.fileName
            color: Suru.foregroundColor

        }
    }

    FormattedText {
        anchors {
            top: documentContainer.bottom
        }

        formattedText: documentContent.caption
        maximumWidth: maximumAvailableContentWidth
        isPreview: message.isCollapsed
    }
}
