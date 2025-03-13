import QtQuick 2.9
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Content 1.3
import "../actions"

Page {

    id: picker

    Component {
        id: resultComponent
        ContentItem {}
    }
    header:UITK.PageHeader{
        title: i18n.tr("Content Picker")
        leadingActionBar.actions:[
            BackAction {
                id: backAction
                enableShortcut: pageStack.currentItem == picker
                onTriggered:{
                    AppActions.view.popFromStack()
                }
            }
        ]
    }

    visible: false
    property var contentUrl
    property var handler
    property var contentType
    property var curTransfer

    function __exportItems(url) {
        if (picker.curTransfer.state === ContentTransfer.InProgress)
        {
            picker.curTransfer.items = [ resultComponent.createObject(parent, {"url": url}) ];
            picker.curTransfer.state = ContentTransfer.Charged;
        }
    }

    ContentPeerPicker {
        visible: parent.visible
        contentType: picker.contentType
        handler: picker.handler
        showTitle: false
        onPeerSelected: {
            picker.curTransfer = peer.request();
            if (picker.curTransfer.state === ContentTransfer.InProgress)
                picker.__exportItems(picker.contentUrl);
            AppActions.view.popFromStack()
        }
        onCancelPressed: {
            AppActions.view.popFromStack()
        }
    }

    Connections {
        target: picker.curTransfer
        onStateChanged: {
            if (picker.curTransfer.state === ContentTransfer.InProgress) {
                picker.__exportItems(picker.contentUrl);
            }
        }
    }
}
