import QtQuick 2.4
import QuickFlux 1.1
import QTelegram 1.0
import Lomiri.PushNotifications 0.1
import "../actions"

Store {

    EnableNotifications {
        id: enableNotifications
        token: pushClient.token
        onError: AppActions.view.showError(i18n.tr("Push Registration Failed"), error)
    }


    PushClient {
        id: pushClient
        appId: "teleports.ubports_teleports"
        onTokenChanged: console.log("Got push token: ", token)
        onError: {
            if ( error === "bad auth" && !settingsStore.u1DialogShown ) {
                AppActions.view.showError(
                            i18n.tr("No Ubuntu One"),
                            i18n.tr("Please connect to Ubuntu One to receive push notifications."),
                            SettingsKey.u1dialogShown
                            )
            }
            else console.warn("👹 Error with pushclient:", error)
        }
    }
}
