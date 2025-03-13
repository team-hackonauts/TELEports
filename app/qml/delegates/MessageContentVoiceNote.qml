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
    property QTdMessageVoiceNote voiceNote: message.content
    property QTdLocalFile voiceLocal: voiceNote.voiceNote.voice.local
    property url localFileSource: voiceNote && voiceLocal.path ? Qt.resolvedUrl("file://" + voiceLocal.path) : ""

    Item {
        id: voiceNoteContainer
        width: maximumAvailableContentWidth
        height:fileIcon.height
        Item {
            id: fileIcon
            width: units.gu(7)
            height: units.gu(7)
            anchors.rightMargin: Suru.units.gu(2)
            UITK.Icon {
                visible: voiceLocal.isDownloadingCompleted
                source: "qrc:/qml/icons/play.svg"
                anchors.fill: parent
            }
            UITK.Icon {
                visible: !voiceLocal.isDownloadingCompleted && !voiceLocal.isDownloadingActive
                source: "qrc:/qml/icons/download.svg"
                anchors.fill: parent
            }
            BusyPercentageIndicator {
                visible: voiceLocal.isDownloadingActive
                anchors.fill: parent
                running: !voiceLocal.isDownloadingCompleted
                percentage: parseInt(voiceLocal.downloadedSize) / parseInt(voiceNote.voiceNote.voice.size) * 100
            }
        }

        TextEdit {
            id:infoLabel
            height: contentHeight
            width: parent.width - fileIcon.width
            wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
            anchors{
                left: fileIcon.right
                right: parent.right
                top: parent.top
                topMargin: Suru.units.gu(1)
                leftMargin: Suru.units.gu(2)
            }
            text: i18n.tr("Voice note") + " " + voiceNote.voiceNote.qmlDuration
            color: Suru.foregroundColor
        }
    }

    FormattedText {
        anchors {
            top: voiceNoteContainer.bottom
            topMargin: message.isOutgoing ? Suru.units.dp(10) : Suru.units.dp(5)
        }

        formattedText: voiceNote.caption
        maximumWidth: maximumAvailableContentWidth
        isPreview: message.isCollapsed
        visible: voiceNote.caption
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (voiceLocal.canBeDownloaded && !voiceLocal.isDownloadingCompleted) {
                voiceNote.voiceNote.voice.downloadFile();
            }
            if(voiceLocal.isDownloadingCompleted){
                messageContentOpening()
                AppActions.view.pushToStack("qrc:///pages/PreviewPage.qml", {
                                                "fileName": voiceNote.voiceNote.voice.fileName,
                                                "audioPreviewSource": localFileSource,
                                                "title": message.sender.displayName,
                                                "subtitle": message.formatDate(message.date)
                                            })
            }
        }
    }
}
