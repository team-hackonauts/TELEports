import QtQuick 2.4
import QuickFlux 1.1
import QTelegram 1.0
import "../actions"

Store {
    property alias stickerSets: stickerSets.stickerSets

    StickerSets {
        id: stickerSets
    }

    Filter {
        type: StickerKey.loadStickerSets

        onDispatched: {
            stickerSets.loadStickerSets()
        }
    }
}
