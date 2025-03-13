import QtQuick 2.9
import QtQuick.Controls 2.2
import Lomiri.Components 1.3 as UITK
import QtQuick.Controls.Suru 2.2

Page {
    id: logoutPage

    property color hf: Suru.foregroundColor
    property color hb: Suru.backgroundColor
    property color hd: Suru.neutralColor

    header: UITK.PageHeader {
        title: i18n.tr('Good bye!')

        UITK.StyleHints {
            foregroundColor: hf
            backgroundColor: hb
            dividerColor: hd
        }
    }
    Column {
        width: Math.min(Suru.units.gu(45), parent.width - units.gu(4))
        spacing: Suru.units.gu(2)
        anchors.centerIn: parent
        Label {
            text: i18n.tr("Disconnecting...")
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
            font.pixelSize: Suru.units.gu(2.5)
        }
        BusyIndicator {
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Label {
            text: i18n.tr("The app will close automatically when the logout process ends.\nPlease, don't close it manually!")
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
        }
    }
}
