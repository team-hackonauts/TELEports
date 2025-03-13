/*
 * Copyright 2018 UBPorts
 * Copyright 2015 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Content 1.1
import "../actions"
import "../components"


Page {
    property string fileName: ""
    property string subtitle: ""
    property url photoPreviewSource
    property url audioPreviewSource
    property url videoPreviewSource

    property bool isPhoto: photoPreviewSource.toString() !== ""
    property bool isAudio: audioPreviewSource.toString() !== ""
    property bool isVideo: videoPreviewSource.toString() !== ""

    id: previewPage
    header:UITK.PageHeader{
        title: previewPage.title
        subtitle: previewPage.subtitle
        leadingActionBar.actions:[
            BackAction {
                id: backAction
                enableShortcut: pageStack.currentItem == previewPage
                onTriggered:{
                    AppActions.view.popFromStack()
                }
            }
        ]
        trailingActionBar.actions: [

            UITK.Action {
                iconName: "share"
                text: i18n.tr("Share")
                onTriggered: save()
                visible: saveAndShareVisible()
            }
        ]
    }

    function saveAndShareVisible() {
        return isPhoto || isVideo || isAudio;
    }

    function save() {
        mediaViewer.reset();

        if (isPhoto) {
            AppActions.view.pushToStack("qrc:///pages/PickerPage.qml", {
                                            "contentUrl": fileName,
                                            "handler": ContentHandler.Destination,
                                            "contentType": ContentType.Pictures
                                        });
        } else if (isVideo) {
            AppActions.view.pushToStack("qrc:///pages/PickerPage.qml", {
                                            "contentUrl": fileName,
                                            "handler": ContentHandler.Destination,
                                            "contentType": ContentType.Videos
                                        });
        }  else if (isAudio) {
            AppActions.view.pushToStack("qrc:///pages/PickerPage.qml", {
                                            "contentUrl": fileName,
                                            "handler": ContentHandler.Destination,
                                            "contentType": ContentType.Music
                                        });
        }
    }


    Item {

        anchors {
            fill: parent
        }

        Rectangle {
            anchors.fill: parent
            color: Suru.backgroundColor
        }

        MediaViewer {
            id: mediaViewer
            anchors.fill: parent
            maxDimension: 2*Math.max(previewPage.width, previewPage.height)
        }
    }

    Component.onCompleted: {
        if (isPhoto) {
            fileName = photoPreviewSource.toString();
        } else if (isVideo) {
            fileName = videoPreviewSource.toString();
        }  else if (isAudio) {
            fileName = audioPreviewSource.toString();
        }
        fileName = fileName.replace("image:\/\/photo\/", "file://");        
    }
}
