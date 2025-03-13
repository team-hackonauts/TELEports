import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Popups 1.3 as UITK_Popups

UITK_Popups.Dialog {
    id: dialogue
    objectName: "dialogWaitCancel"

    property var progress: -1
    property var cancelButtonText: i18n.tr("Cancel")
    property var cancelButtonColor: Suru.theme == Suru.Dark ? UITK.LomiriColors.ash : UITK.LomiriColors.graphite

    signal finished();
    signal cancelled();

    text: dialogue.text

    ProgressBar {
        value: progress
        indeterminate: progress < 0
    }

    UITK.Button {
        text: dialogue.cancelButtonText
        color: dialogue.cancelButtonColor
        onClicked: {
            dialogue.cancelled();
            UITK_Popups.PopupUtils.close(dialogue)
        }
    }
}
