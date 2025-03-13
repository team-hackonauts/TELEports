import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QTelegram 1.0

Column {
    property var isPreview: false
    property var maximumWidth: 0
    property QTdFormattedText formattedText: null

    spacing: Suru.units.gu(2)

    width: textEdit.width

    TextEdit {
        id: textEdit

        height: contentHeight
        width: Math.min(maximumWidth, implicitWidth)
        readOnly: true
        text: isPreview ? (elidedTextMetrics ? elidedTextMetrics.elidedText : '') : (formattedText ? formattedText.text : '')
        color: Suru.foregroundColor
        Suru.textStyle: Suru.PrimaryText
        selectedTextColor: Suru.highlightColor
        wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
        onLinkActivated: {
            const url = link.match(/^([a-zA-Z]*?):\/\//g) ? link : `https://${link}`;
            Qt.openUrlExternally(url);
        }
    }

    TextMetrics {
        id: elidedTextMetrics
        text: formattedText ? formattedText.text : ''
        elide: Text.ElideRight
        elideWidth: Math.max(maximumWidth, textEdit.width) - Suru.units.gu(2)
    }

    // Only load the formatter if there are
    // entities to be formatted.
    Loader {
        id: formatter
        active: !isPreview && formattedText && formattedText.entities.count > 0
        asynchronous: true
        sourceComponent: Component {
            Item {
                TextFormatter {
                    id: textFormatter
                    codeColor: Suru.foregroundColor
                    linkColor: Suru.highlightColor
                    spoilerForeground: "transparent"
                    spoilerBackground: Suru.foregroundColor
                    textDocument: textEdit.textDocument
                    content: formattedText
                    Suru.theme: rootItem.Suru.theme
                    Suru.textStyle: Suru.TertiaryText
                }
            }
        }
    }
}
