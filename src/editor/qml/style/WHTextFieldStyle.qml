import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2

import "."

TextFieldStyle {
    textColor: Style.text
    selectedTextColor: Style.text
    placeholderTextColor: Style.mid
    selectionColor: Style.highlight
    background: Rectangle {
        id: input

        implicitWidth: 20 * Screen.pixelDensity
        implicitHeight: 6 * Screen.pixelDensity

        color: Style.alternateBase
        border.width: 1
        border.color: Style.dark

        states: [
            State {
                name: "active"
                when: control.hovered || control.activeFocus
                PropertyChanges { target: input.border; color: Style.highlight }
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
}

