import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import QTelegram 1.0
import "../components"

MessageContentBase {
    id: item
    property QTdMessageCall call: message ? message.content : null

    Column {
        anchors {
            top: parent.top
        }

        width: l1.contentWidth + Suru.units.gu(6)

        RowLayout {
            id: row
            height: Math.max(Suru.units.gu(3), c.height)
            width: parent.width

            Column {
                id: c
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                Label {
                    id: l1
                    Suru.highlightType: {
                        if (!call) {
                            return null
                        }
                        switch(call.discardReason.type) {
                        case QTdObject.CALL_DISCARD_REASON_DECLINED:
                            return Suru.NegativeHighlight
                        case QTdObject.CALL_DISCARD_REASON_DISCONNECTED:
                        case QTdObject.CALL_DISCARD_REASON_EMPTY:
                            return Suru.WarningHighlight
                        case QTdObject.CALL_DISCARD_REASON_HUNG_UP:
                            return Suru.PositiveHighlight
                        case QTdObject.CALL_DISCARD_REASON_MISSED:
                            return Suru.InformationHighlight
                        }
                    }
                    Suru.textStyle: Suru.SecondaryText
                    color: Suru.highlightColor

                    text: call ? call.typeText.split("(")[0] : ''
                }

                Label {
                    visible: call ? call.duration > 0 : false
                    readonly property int hours: call ? Math.floor(call.duration / 3600) : 0
                    readonly property string hoursString: (hours < 10 ? "0%1" : "%1").arg(hours)
                    readonly property int minutes: call ? Math.floor(call.duration / 60 - hours * 60) : 0
                    readonly property string minutesString: (minutes < 10 ? "0%1" : "%1").arg(minutes)
                    readonly property int seconds: call ? (call.duration - hours * 3600 - minutes * 60) : 0
                    readonly property string secondsString: (seconds < 10 ? "0%1" : "%1").arg(seconds)
                    //TRANSLATORS: This is the duration of a phone call in hours:minutes:seconds format
                    text: i18n.tr("Duration: %1:%2:%3").arg(hoursString).arg(minutesString).arg(secondsString)
                    Suru.textLevel: Suru.Small
                    Suru.textStyle: Suru.TertiaryText
                }
            }

            UITK.StyledItem {
                height: units.gu(3)
                width: height
                Layout.alignment: Qt.AlignVCenter
                UITK.Icon {
                    width: parent.width
                    height: parent.height
                    name: "call-stop"
                }
            }
        }
    }
}
