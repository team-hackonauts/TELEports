// Copyright 2022 Maciej Sopyło <me@klh.io>
// 
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

import Lomiri.Components 1.3 as UITK
import Lomiri.Components.Pickers 1.3
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Suru 2.2
import QtQuick.Layouts 1.3

Column {
  id: dateTimePicker
  width: parent.width
  spacing: Suru.units.gu(1)


  property var date: new Date()
  property string mode: "date"

  RowLayout {
    width: parent.width

    UITK.TextField {
      Layout.preferredWidth: parent.width / 2
      readOnly: true
      text: Qt.formatDate(dateTimePicker.date, Qt.locale().dateFormat(Locale.ShortFormat))

      MouseArea {
        anchors.fill: parent
        onClicked: {
          dateTimePicker.mode = "date";
        }
      }

      Rectangle {
        anchors {
          top: parent.bottom
        }
        width: parent.width
        height: 2
        color: theme.palette.selected.positionText
        opacity: dateTimePicker.mode === "date" ? 1 : 0

        Behavior on opacity {
          NumberAnimation { duration: 200 }
        }
      }
    }

    UITK.TextField {
      Layout.preferredWidth: parent.width / 2
      readOnly: true
      // remove "t" from the format, so we get seconds and am/pm without timezone
      text: Qt.formatTime(dateTimePicker.date, Qt.locale().timeFormat(Locale.LongFormat).replace(" t", ""))
      horizontalAlignment: TextInput.AlignRight

      MouseArea {
        anchors.fill: parent
        onClicked: {
          dateTimePicker.mode = "time";
        }
      }

      Rectangle {
        anchors {
          top: parent.bottom
        }
        width: parent.width
        height: 2
        color: theme.palette.selected.positionText
        opacity: dateTimePicker.mode === "time" ? 1 : 0

        Behavior on opacity {
          NumberAnimation { duration: 200 }
        }
      }
    }
  }

  DatePicker {
    id: datePicker
    property alias date: dateTimePicker.date
    mode: "Days|Months|Years"
    visible: dateTimePicker.mode === "date"
    
    transform: Translate { x: -units.gu(3) }
  }

  DatePicker {
    id: timePicker
    property alias date: dateTimePicker.date
    mode: "Hours|Minutes|Seconds"
    visible: dateTimePicker.mode === "time"
    
    transform: Translate { x: -units.gu(3) }
  }
}
