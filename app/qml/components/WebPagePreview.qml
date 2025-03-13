import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QTelegram 1.0
import "../actions"

Item {
    property QTdWebPage preview: null
    property bool imageOnly: !(siteName.visible || title.visible || description.visible)

    height: imageOnly ? previewImage.height : pageDescription.height
    Rectangle {
        id: colorBlock
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        width: Suru.units.dp(3)
        color: Suru.foregroundColor
        opacity: 0.8
    }

    RowLayout {
        anchors {
            left: colorBlock.right
            leftMargin: Suru.units.gu(1)
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }

        Column {
            id: pageDescription
            visible: !imageOnly
            Layout.fillWidth: true
            Layout.maximumWidth: parent.width

            Label {
                id: siteName
                width: parent.width
                color: Suru.highlightColor
                text: preview.siteName
                Suru.textStyle: Suru.SecondaryText
                Suru.textLevel: Suru.Paragraph
                font.weight: Font.DemiBold
                elide: Text.ElideRight
                visible: text != ""
            }
            Label {
                id: title
                width: parent.width
                text: preview.title
                Suru.textStyle: Suru.SecondaryText
                Suru.textLevel: Suru.Paragraph
                font.weight: Font.DemiBold
                wrapMode: Text.Wrap
                maximumLineCount: 2
                elide: Text.ElideRight
                visible: text != ""
            }
            Label {
                id: description
                width: parent.width
                text: preview.description
                wrapMode: Text.Wrap
                maximumLineCount: title.lineCount == 2 ? 2 : 3
                elide: Text.ElideRight
                Suru.textStyle: Suru.TertiaryText
                Suru.textLevel: Suru.Caption
                visible: text != ""
            }
        }

        UITK.LomiriShape {
            id: previewImage
            aspect: UITK.LomiriShape.Flat
            sourceFillMode: UITK.LomiriShape.PreserveAspectCrop
            visible: preview.photo.sizes.count > 0 &&  imageOnly ? true : parent.width > Suru.units.gu(20)
            Layout.preferredWidth: imageOnly ? parent.width : height
            Layout.preferredHeight: imageOnly ? width * source.height / source.width : implicitHeight
            Layout.maximumHeight: imageOnly ? parent.width : pageDescription.height
            Layout.alignment: Qt.AlignBottom //Qt.AlignVCenter

            source: Image {
                asynchronous: true
                source: preview.photo.sizes.count > 0 ? Qt.resolvedUrl("image://photo/" + preview.photo.sizes.get(imageOnly ? 2 : 1).photo.local.path) : ""
            }


            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (preview.type=="photo") {
                        var largeSize = preview.photo.sizes.getLast();
                        var largePhoto = largeSize.photo;
                        if (largePhoto.canBeDownloaded && !largePhoto.isDownloadingCompleted) {
                            largePhoto.downloadFile();
                        }
                        AppActions.view.pushToStack("qrc:///pages/PreviewPage.qml", {
                                            "photoPreviewSource": Qt.resolvedUrl("image://photo/" + largePhoto.local.path),
                                                "title": message.sender.displayName,
                                                "subtitle": message.formatDate(message.date)
                                        })
                    } else {
                        Qt.openUrlExternally(preview.url)
                    }
                }
            }
        }
    }
}
