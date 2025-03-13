import QtQuick 2.9

MessageBarItem {
    text: message ? content.label : i18n.tr("Missing label...")
}
