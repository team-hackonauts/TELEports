import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Content 1.1 as ContentHub
import QTelegram 1.0
import "../actions"

PopupDialog {
    id: sendMediaDialog
    property var mediaType
    property string incomingText
    property var fileNames
    property string replyId
    property bool forcedUncompressedBySystem: false
    property bool sendUncompressed: false
    property bool sendAsAlbum: true
    text: mediaType === ContentHub.ContentType.Text || mediaType === ContentHub.ContentType.Links ?
        i18n.tr("Would you like to send text?") :
        i18n.tr("Would you like to send file?", "Would you like to send files?", fileNames.length)
    confirmButtonColor: theme.palette.normal.focus
    confirmButtonText: i18n.tr("Send")
    onConfirmed: {
        let captionText = caption.text.trim();

        switch (mediaType) {
            case ContentHub.ContentType.Pictures:
                sendPictures(captionText, replyId);
                break;
            case ContentHub.ContentType.Music:
                sendSingleOrAlbum(fileNames, captionText, replyId, AppActions.chat.sendAudio, AppActions.chat.sendAudioAlbum);
                break;
            case ContentHub.ContentType.Videos:
                sendSingleOrAlbum(fileNames, captionText, replyId, AppActions.chat.sendVideo, AppActions.chat.sendVideoAlbum);
                break;
            case ContentHub.ContentType.Documents:
                sendSingleOrAlbum(fileNames, captionText, replyId, AppActions.chat.sendDocument, AppActions.chat.sendDocumentAlbum);
                break;
            default:
                if (captionText.length > 0 && mediaType === ContentHub.ContentType.Contacts) {
                    AppActions.chat.sendMessage(captionText, replyId);
                    captionText = "";
                }
                for (let i = 0; i < fileNames.length; i++) {
                    switch (mediaType) {
                        case ContentHub.ContentType.Contacts:
                            AppActions.chat.sendContact(fileNames[i], replyId);
                            break;
                        case ContentHub.ContentType.Text:
                        case ContentHub.ContentType.Links:
                            AppActions.chat.sendMessage(captionText, replyId);
                            break;
                        default:
                            AppActions.chat.sendDocument(fileNames[i], captionText, replyId);
                    }
                }
                break;
        }
        if (replyId > 0) {
            AppActions.chat.clearReply();
        }
    }

    ListModel {
        id: filesToSend
    }

    Column {
        id: col

        anchors {
            left: parent.left
            right: parent.right
        }
        spacing: units.gu(1)

        Row {
            id: row
            spacing: 24
            bottomPadding: 24
            visible: mediaType === ContentHub.ContentType.Pictures

            UITK.CheckBox {
                id: checkBox
                enabled: !sendMediaDialog.forcedUncompressedBySystem
                checked: sendMediaDialog.forcedUncompressedBySystem
                onCheckedChanged: sendMediaDialog.sendUncompressed = checked
            }
            UITK.Label {
                id: label
                text: i18n.tr("Send uncompressed")
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (sendMediaDialog.forcedUncompressedBySystem) {
                            return
                        }
                        checkBox.checked = !checkBox.checked
                    }
                }
            }
        }

        Row {
            id: sendAsAlbumRow
            spacing: 24
            bottomPadding: 24
            visible: fileNames.length >1 && (mediaType === ContentHub.ContentType.Pictures || mediaType === ContentHub.ContentType.Videos
                || mediaType === ContentHub.ContentType.Music || mediaType === ContentHub.ContentType.Documents)

            UITK.CheckBox {
                id: sendAsAlbumCheckBox
                enabled: !sendMediaDialog.forcedUncompressedBySystem
                checked: !sendMediaDialog.forcedUncompressedBySystem
                onCheckedChanged: sendMediaDialog.sendAsAlbum = checked
            }
            UITK.Label {
                id: sendAsAlbumLabel
                text: i18n.tr("Send as album")
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (sendMediaDialog.forcedUncompressedBySystem) {
                            return
                        }
                        sendAsAlbumCheckBox.checked = !sendAsAlbumCheckBox.checked
                    }
                }
            }
        }

        GridView {
            id: photosGrid
            width: parent.width
            height: units.gu(20)
            cellWidth: units.gu(9.5)
            cellHeight: units.gu(9.5)
            visible: mediaType === ContentHub.ContentType.Pictures
            clip: true

            model: filesToSend
            delegate: Image {
                id: thumbnail
                source: "image://photo/%1".arg(path)
                height: units.gu(9)
                width: units.gu(9)
                fillMode: Image.PreserveAspectCrop
            }
        }

        UITK.TextArea {
            id: caption
            height: photosGrid.visible ? units.gu(6) : units.gu(10)
            width: parent.width
            placeholderText: i18n.tr("Enter optional message...")
            text: incomingText
        }
    }

    QTdMediaSizeExtractor {
        id: mediaSizeExtractor
    }

    Component.onCompleted: {
        if (mediaType !== ContentHub.ContentType.Pictures) {
            return;
        }
        setConfirmButtonEnabled(false)
        for (const i in fileNames) {
            const fileName = fileNames[i]
            sendMediaDialog.forcedUncompressedBySystem = sendMediaDialog.forcedUncompressedBySystem || !mediaSizeExtractor.canBeSendCompressed(fileName)
            filesToSend.append({
                "path": fileName
            })
        }
        setConfirmButtonEnabled(true)
    }

    function sendPictures(captionText, replyId) {
        const files = []
        for (let i = 0; i < filesToSend.count; i++) {
            files.push(filesToSend.get(i).path)
        }
        if (sendMediaDialog.forcedUncompressedBySystem || sendMediaDialog.sendUncompressed) {
            sendSingleOrAlbum(files, captionText, replyId, AppActions.chat.sendDocument, AppActions.chat.sendDocumentAlbum);
        } else {
            sendSingleOrAlbum(files, captionText, replyId, AppActions.chat.sendPhoto, AppActions.chat.sendPhotoAlbum);
        }
    }

    function sendSingleOrAlbum(fileNames, captionText, replyId, callBackSingle, callBackAlbum) {
        if (fileNames.length === 1 || !sendMediaDialog.sendAsAlbum) {
            callBackSingle(fileNames[0], captionText, replyId);
            for (let i = 1; i < fileNames.length; i++) {
                callBackSingle(fileNames[i], "", replyId);
            }
        } else {
            callBackAlbum(fileNames, captionText, replyId);
        }
    }
}
