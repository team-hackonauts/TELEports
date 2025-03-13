import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QTelegram 1.0

Item {
    width: childrenRect.width
    height: childrenRect.height

    Label {
        text: i18n.tr("Message Unavailable...")
        width: contentWidth
        height: Suru.units.gu(2.5)
    }
}
