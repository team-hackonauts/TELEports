import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QTelegram 1.0

MessageBubbleItem {
    id: bubble
    MessageContentCall {
        message: bubble.message
    }
}
