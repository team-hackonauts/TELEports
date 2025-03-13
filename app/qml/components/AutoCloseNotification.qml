/*
 * Copyright (C) 2023 UBPorts
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.9
import QtQuick.Controls.Suru 2.2
import Lomiri.Components 1.3

LomiriShape {
    id: rootItem
    property alias text: label.text
    property int displayTime: 2500

    anchors {
        horizontalCenter: parent.horizontalCenter
        bottom: parent.bottom
        bottomMargin: units.gu(3)
    }
    color: Suru.secondaryForegroundColor
    aspect: LomiriShape.Flat
    width: label.width + units.gu(1.5)
    height: label.height + units.gu(1.5)

    Label {
        id: label
        anchors.centerIn: parent
        color: Suru.backgroundColor
    }

    SequentialAnimation {
        id: showAnimation
        running: true
        NumberAnimation { target: rootItem; property: "opacity"; to: 0.9; duration: 500 }
        PauseAnimation { duration: displayTime }
        ScriptAction { script: destroyAnimation.restart() }
    }

    SequentialAnimation {
        id: destroyAnimation
        NumberAnimation { target: rootItem; property: "opacity"; to: 0; duration: 500 }
        ScriptAction {
            script: {
                rootItem.destroy()
            }
        }
    }
}
