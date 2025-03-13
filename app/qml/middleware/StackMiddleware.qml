import QtQuick 2.9
import QuickFlux 1.1
import Lomiri.Components 1.3
import Lomiri.Components.Popups 1.3
import "../actions"

Middleware {
    filterFunctionEnabled: true

    property var stack

    function pushToStack(message) {
        stack.push(message.view, message.properties)
    }

    function replaceOnStack(message) {
        if (stack.depth) {
            stack.clear()
        }
        stack.push(message.view, message.properties)
    }

    function popFromStack(message) {
        stack.pop()
    }

    function popAllButOneFromStack(message) {
        stack.pop(null)
    }

    function showAutoCloseNotification(message) {
        const component = Qt.createComponent("/components/AutoCloseNotification.qml");
        const sprite = component.createObject(stack.currentItem, {text: message.text})
        if (sprite == null) {
            console.log("Error creating AutoCloseNotification")
        }
    }
}
