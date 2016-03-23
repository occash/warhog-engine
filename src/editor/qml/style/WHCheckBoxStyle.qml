import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2

import "."

CheckBoxStyle {
    indicator: Rectangle {
        id: button

        implicitWidth: 4 * Screen.pixelDensity
        implicitHeight: 4 * Screen.pixelDensity

        color: Style.alternateBase
        border.color: Style.alternateBase

        Rectangle {
            visible: control.checked
            color: Style.text
            anchors.margins: 1 * Screen.pixelDensity
            anchors.fill: parent
        }

        states: [
            State {
                name: "active"
                when: control.hovered || control.pressed
                PropertyChanges { target: button.border; color: Style.highlight }
            }
        ]

        transitions: [
            Transition {
                to: ""
                ColorAnimation { property: "color" }
            },
            Transition {
                to: "active"
                ColorAnimation { property: "color" }
            }
        ]
    }

    label: Text {
        color: Style.text
        text: control.text
    }
}

