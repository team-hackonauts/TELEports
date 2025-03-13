import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import Ubuntu.Components 1.3 as UITK
import QtMultimedia 5.8
import QTelegram 1.0
import QuickFlux 1.1
import QtGraphicalEffects 1.0
import "../actions"
import "../components"

MessageContentBase {
    id: root

    property QtObject poll: message.content.poll
    property var optionIds: new Map()

    function togglePollOption(optionId) {
        if (!poll.isMultiChoice) {
            AppActions.chat.setPollAnswer(message.chatId, message.id, [ optionId ]);
        } else {
            optionIds.set(optionId, !optionIds.get(optionId));
        }
    }

    function addPollOptionIndex(optionId, isChosen) {
        optionIds.set(optionId, isChosen);
    }

    ColumnLayout {
        id: outerLayout
        width: maximumAvailableContentWidth
        spacing: units.gu(1.5)
        UITK.Label {
            id: questionText
            Layout.preferredWidth: width
            Layout.fillWidth: true
            text: poll.question
            font.bold: true
            color: Suru.foregroundColor
            Suru.textStyle: Suru.PrimaryText
            wrapMode: Label.WordWrap
        }
        UITK.Label {
            Layout.preferredWidth: width
            Layout.fillWidth: true
            visible: (poll.isAnonymous || poll.isClosed)
            text: {
                if (poll.isClosed) {
                    return i18n.tr("Final result");
                } else if (poll.isAnonymous) {
                    return i18n.tr("Anonymous Poll");
                }
                return "";
            }
        }

        Repeater {
            model: poll.options
            delegate: Item {
                Layout.preferredHeight: innerLayout.childrenRect.height
                Layout.preferredWidth: maximumAvailableContentWidth
                GridLayout {
                    id: innerLayout
                    columns: 2
                    anchors.fill:parent
                    rowSpacing: units.dp(3)
                    Item {
                        id: statusItem
                        Layout.alignment: Qt.AlignTop
                        Layout.minimumWidth: spacerText.width
                        UITK.Label {
                            id: spacerText
                            text: "100%"
                            opacity: 0
                        }
                        UITK.Label {
                            text: modelData.percentage + "%"
                            opacity: poll.userHasChosen || poll.isClosed ? 1 : 0
                        }
                        UITK.Icon {
                            width: units.gu(2)
                            height: width
                            name: "ok"
                            color: theme.palette.normal.activity
                            opacity: modelData.isBeingChosen && !poll.userHasChosen && !poll.isClosed  ? 1: 0
                        }
                        Rectangle {
                            width: units.gu(2)
                            height: width
                            border.color: theme.palette.normal.activity
                            border.width: 1
                            radius: width * 0.5
                            opacity: !modelData.isBeingChosen && !poll.userHasChosen && !poll.isClosed ? 1 : 0
                        }
                    }
                    UITK.Label {
                        id: optionText
                        Layout.preferredWidth: width
                        Layout.fillWidth: true
                        text: modelData.text
                        color: Suru.foregroundColor
                        Suru.textStyle: Suru.PrimaryText
                        wrapMode: Label.WordWrap
                    }
                    Item {
                        Layout.alignment: Qt.AlignTop | Qt.AlignRight
                        Layout.minimumWidth: childrenRect.width
                        opacity: poll.userHasChosen && modelData.isChosen ? 1 : 0
                        Rectangle {
                            width: units.gu(1.5)
                            height: width
                            radius: units.dp(2)
                            color: theme.palette.normal.positive
                        }
                        UITK.Icon {
                            width: units.gu(1.5)
                            height: width
                            name: "ok"
                            color: theme.palette.normal.background
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                        Rectangle {
                            width: optionText.width * modelData.percentage / 100
                            height: units.gu(1)
                            color: modelData.isChosen ? theme.palette.normal.positive : theme.palette.normal.activity
                        }
                    }
                    Rectangle {
                        // bottom spacer
                        height: poll.userHasChosen && modelData.isChosen ? units.gu(1) : units.gu(0)
                        color: transparent
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    enabled: !poll.userHasChosen
                    onClicked: {
                        if (!modelData.isClosed) {
                            modelData.isBeingChosen = !modelData.isBeingChosen
                            root.togglePollOption(modelData.optionIndex)
                        }
                    }
                    Component.onCompleted: root.addPollOptionIndex(modelData.optionIndex, modelData.isChosen)
                }
            }
        }

        UITK.Button {
            Layout.alignment: Qt.AlignHCenter
            visible: (poll.isMultiChoice || poll.userHasChosen) && !poll.isClosed
            text: poll.userHasChosen ? i18n.tr("Reset vote") : i18n.tr("Vote!")
            color: theme.palette.normal.activity
            onClicked: {
                const selectedOptions = Array.from(optionIds.entries())
                    .filter(([ key, value ]) => value)
                    .map(([ key ]) => key);
            AppActions.chat.setPollAnswer(message.chatId, message.id, poll.userHasChosen ? [] : selectedOptions);
            }
        }

        UITK.Label {
            text: poll.totalVoters == 0 ? i18n.tr("No votes yet") : i18n.tr("%1 vote", "%1 votes", poll.totalVoters).arg(poll.totalVoters)
        }
    }
}
