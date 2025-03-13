import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Suru 2.2
import QTelegram 1.0
import QLottieFrameProvider 1.0
import "../stores"
import "../actions"

Item {
    property QTdStickerSet currentStickerSet: Telegram.stickers.stickerSets.get(stickerSetSelection.currentIndex)

    signal sendStickerRequested(var sticker)

    RowLayout {
        anchors.fill: parent

        ListView {
            id: stickerSetSelection

            Layout.fillHeight: true
            Layout.topMargin: units.dp(2) // border
            implicitWidth: units.gu(6)

            model: Telegram.stickers.stickerSets
            orientation: Qt.Vertical
            clip: true
            currentIndex: 0

            delegate: Item {
                id: stickerSetDelegate

                property bool isFirst: index == 0
                property bool isLast: index == (stickerSetSelection.count - 1)

                property QTdStickerSet stickerSet: Telegram.stickers.stickerSets.get(index)
                property QTdFile thumbnailFile: stickerSet.thumbnail.file
                property QTdLocalFile localFile: thumbnailFile.local
                property bool isThumbnailAnimated: stickerSet.thumbnail.format.type === QTdObject.THUMBNAIL_FORMAT_TGS

                property string localFileSource: localFile && localFile.path !== ""
                    ? isThumbnailAnimated 
                        ? "file://" + localFile.path
                        : "image://photo/" + localFile.path
                    : ""

                width: units.gu(6)
                height: units.gu(5)
                        + (isFirst ? units.gu(1) : 0)
                        + (isLast ? units.gu(1) : 0)

                Connections {
                    target: thumbnailFile
                    onFileChanged: {
                        thumbnailLoader.item.reload();
                    }
                }

                Connections {
                    target: stickerSetDelegate.stickerSet
                    onStickerSetChanged: {
                        // Trigger reload of sticker grid
                        stickerSetSelection.currentIndexChanged();
                    }
                }

                Component.onCompleted: {
                    if (localFile.canBeDownloaded && !localFile.isDownloadingCompleted) {
                        thumbnailFile.downloadFile();
                    }
                    if (stickerSetSelection.currentIndex == index) {
                        stickerSetDelegate.stickerSet.loadDetails();
                    }
                }

                Loader {
                    id: thumbnailLoader
                    sourceComponent: isThumbnailAnimated ? thumbnailAnimated : thumbnailStatic
                    anchors {
                        fill: parent
                        topMargin: units.dp(4) + (isFirst ? units.gu(1) : 0)
                        bottomMargin: units.dp(4) + (isLast ? units.gu(1) : 0)
                        leftMargin: units.gu(1)
                        rightMargin: units.gu(1)
                    }
                }

                Component {
                    id: thumbnailAnimated
                    LottieAnimation {
                        source: isThumbnailAnimated ? localFileSource : ''
                        anchors.fill: parent
                        play: true

                        function reload() {
                            source = "";
                            source = localFileSource;
                            play = true
                        }
                    }
                }

                Component {
                    id: thumbnailStatic

                    Image {
                        source: !isThumbnailAnimated ? localFileSource : ''
                        sourceSize.width: width
                        sourceSize.height: height
                        asynchronous: true
                        anchors.fill: parent

                        function reload() {
                            source = "";
                            source = localFileSource;
                        }
                    }
                }

                Rectangle {
                    anchors {
                        top: parent.top
                        right: parent.right
                        bottom: parent.bottom
                        topMargin: isFirst ? units.gu(1) : 0
                        bottomMargin: isLast ? units.gu(1) : 0
                    }
                    width: units.dp(2)
                    color: Suru.highlightColor
                    visible: index == stickerSetSelection.currentIndex
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stickerSetDelegate.stickerSet.loadDetails();
                        stickerSetSelection.currentIndex = index;
                    }
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.topMargin: units.gu(1)
            Layout.bottomMargin: units.gu(1)
            implicitWidth: units.dp(1)
            color: Suru.neutralColor
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: units.dp(2) // border

            GridView {
                id: gridView

                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    horizontalCenter: parent.horizontalCenter
                }

                width: parent.width - (parent.width % cellWidth)

                clip: true

                model: currentStickerSet !== null ? currentStickerSet.stickers : []

                cellWidth: units.gu(8) + d.stickerSpacing
                cellHeight: units.gu(8) + d.stickerSpacing

                delegate: Item {
                    width: gridView.cellWidth
                    height: gridView.cellHeight

                    Image {
                        id: image

                        anchors {
                            fill: parent
                            margins: d.stickerSpacing
                        }

                        clip: true

                        property QTdSticker sticker: currentStickerSet.stickers.get(index)
                        property QTdFile file: sticker.thumbnail.file
                        property QTdLocalFile localFile: file.local

                        property string localFileSource: localFile && localFile.path !== ""
                            ? "image://photo/" + localFile.path
                            : ""

                        function reload() {
                            image.source = "";
                            image.source = localFileSource;
                        }

                        source: localFileSource
                        asynchronous: true
                        sourceSize.width: gridView.cellWidth - d.stickerSpacing
                        sourceSize.height: gridView.cellHeight - d.stickerSpacing

                        Connections {
                            target: image.file
                            onFileChanged: {
                                image.reload();
                            }
                        }

                        Component.onCompleted: {
                            if (image.localFile.canBeDownloaded && !image.localFile.isDownloadingCompleted) {
                                image.file.downloadFile();
                            }
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            sendStickerRequested(image.sticker);
                        }
                    }
                }

                QtObject {
                    id: d

                    property int stickerSpacing: units.dp(4)
                }
            }
        }
    }

    Component.onCompleted: {
        StickerActions.loadStickerSets();
    }
}
