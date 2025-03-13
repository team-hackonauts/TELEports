import QtQuick 2.9
import QuickFlux 1.1
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3
import QTelegram 1.0
import "../actions"
import "../components"
import "../stores"

PopupDialog {
        property int currentTTL
        property QTdChat secretChat
        UITK.Label {
        anchors.horizontalCenter: parent.horizontalCenter
        text: i18n.tr("Self-destruct timer for messages in this chat:")
        horizontalAlignment: Text.AlignHCenter
        width: parent.width
        maximumLineCount: 2
        elide: Text.ElideRight
        wrapMode: Text.Wrap
    }
    Slider{
        function translatettl(ttlSeconds) {
            if (ttlSeconds <= 15) {
                return ttlSeconds
            }
            switch(ttlSeconds) {
                case 30:
                    return 16;
                case 60:
                    return 17;
                case 3600:
                    return 18;
                case 86400:
                    return 19;
                case 604800:
                    return 20;
            }
            return 16;
        }
        id: ttlSlider
        property int ttlSeconds: 0
        snapMode: Slider.SnapAlways
        from: 0
        to: 20
        stepSize: 1
        value: translatettl(secretChat.ttl)
        onValueChanged: {
            switch(value) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    ttlText.text = i18n.tr("%1 second", "%1 seconds", value).arg(value)
                    ttlSeconds = value
                    break;
                case 16:
                    ttlText.text = i18n.tr("%1 second", "%1 seconds", value).arg(30)
                    ttlSeconds = 30
                    break;
                case 17:
                    ttlText.text = i18n.tr("1 minute")
                    ttlSeconds = 60
                    break;
                case 18:
                    ttlText.text = i18n.tr("1 hour")
                    ttlSeconds = 3600
                    break;
                case 19:
                    ttlText.text = i18n.tr("1 day")
                    ttlSeconds = 86400
                    break;
                case 20:
                    ttlText.text = i18n.tr("1 week")
                    ttlSeconds = 604800
                    break;
                default:
                    ttlText.text = i18n.tr("Off")
                    ttlSeconds = 0
                    break;
            }
        }
    }

    UITK.Label {
        id: ttlText
        anchors.left: parent.left
        horizontalAlignment: Text.Left
        width: parent.width
    }
    onConfirmed: AppActions.chat.sendSetTTL(secretChat.id, ttlSlider.ttlSeconds)
}
