import QtQuick 2.9
import QtQuick.Window 2.4
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QuickFlux 1.1
import QTelegram 1.0
import "./actions"
import "./components"
import "./middleware"
import "./stores"

UITK.MainView {
    id: root
    /**
     * Only show the window once we have reached a state
     * that has something to display.
     * TODO: Unless we want to show a progress spinner or something
     * during the AuthStateWaitTdParams and AuthStateWaitEncryptionKey
     * state???
     */
    visible: Telegram.auth.state > AuthState.WaitEncryptionKey
    width: Suru.units.gu(45)
    height: Suru.units.gu(75)
    property bool landscape: width > height
    readonly property bool tablet: landscape ? width >= units.gu(90) : height >= units.gu(90)
    theme.name: Telegram.settingsStore.uitkTheme
    anchorToKeyboard: true
    applicationName: "teleports.ubports"

    Item {
        id: rootItem
        Suru.theme: Telegram.settingsStore.theme
        anchors.fill: parent

        StackView {
            id: pageStack
            anchors {
                fill: parent
            }
        }

        MiddlewareList {
            applyTarget: AppDispatcher
            /**
             * View Middleware
             *
             * Used for showing errors, conrolling the stack etc
             */
            StackMiddleware {
                stack: pageStack
            }
            ErrorsMiddleware {}

            /**
             * Chat Middleware
             */
            ChatMiddleware {}

            SettingsMiddleware {}
        }
    }

    // Placed in MainView for convenience.
    function flickable_responsive_scroll_fix(flickable) {
        // "Screen.devicePixelRatio === 1" means scaling is managed by the OS, in that case tune scroll velocity, otherwise let Qt do the job
        if (Screen.devicePixelRatio === 1 ) {
            var scaleFactor = units.gridUnit / 8;
            flickable.maximumFlickVelocity = flickable.maximumFlickVelocity * scaleFactor;
            flickable.flickDeceleration = flickable.flickDeceleration * scaleFactor;
        }
    }

    Connections {
      target: Qt.application
      onAboutToQuit: {
        pageStack.clear()
        AppActions.auth.shutDown();
      }
    }
}
