import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QTelegram 1.0
import QuickFlux 1.1
import "../components"
import QLottieFrameProvider 1.0

MessageContentBase {
    property QTdMessageSticker stickerContent: message.content
    property QTdFile file: stickerContent.sticker.sticker
    // TODO: Consider thumbnail
    // property QTdFile thumbnail: stickerContent.sticker.thumbnail
    property QTdLocalFile localFile: file.local
    property url localFileSource: localFile.path !== "" ? Qt.resolvedUrl("file://" + localFile.path) : Qt.resolvedUrl("")

    Loader {
        id: stickerLoader
        // TODO: Handle WebM stickers
        sourceComponent: {
            if (stickerContent.sticker.stickerFormat.type === QTdObject.STICKER_FORMAT_TGS) {
                return lottie;
            } else if (stickerContent.sticker.stickerFormat.type === QTdObject.STICKER_FORMAT_WEBP) {
                return webpSticker;
            }
        }
        width: Math.min(d.maxStickerSize, maximumAvailableContentWidth)
        height: width * (stickerContent.sticker.height/stickerContent.sticker.width)
    }
    Component {
        id: webpSticker
        AnimatedImage {
            asynchronous: true
            source: localFileSource

            function reload() {
                source = localFileSource
                playing = true
            }

            Component.onCompleted: playing = true
        }
    }
    Component {
        id: lottie
        LottieAnimation {
            source: localFileSource

            function reload() {
                source = localFileSource
                play = true
            }

            Component.onCompleted: play = true
        }
    }
    Connections {
        target: file
        onFileChanged: stickerLoader.item.reload()
    }

    QtObject {
        id: d

        // TODO: dynamically adjust
        readonly property int maxStickerSize: message.isCollapsed ? Suru.units.gu(20/5) : Suru.units.gu(20)
    }

    Component.onCompleted: {
        if (localFile.canBeDownloaded && !localFile.isDownloadingCompleted) {
            file.downloadFile();
        }
    }
}
