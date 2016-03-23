import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2

import "."

SpinBoxStyle {
    textColor: Style.text
    selectedTextColor: Style.text
    selectionColor: Style.highlight
    background: Rectangle {
        id: input

        implicitWidth: 20 * Screen.pixelDensity
        implicitHeight: 5 * Screen.pixelDensity

        color: Style.alternateBase
        border.width: 1
        border.color: Style.alternateBase

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
    incrementControl: Item {
        implicitWidth: padding.right
        Image {
            source: "../images/arrow_up.png"
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 1
            //opacity: control.enabled ? (styleData.upPressed ? 1 : 0.6) : 0.5
            width: 3 * Screen.pixelDensity
            fillMode: Image.PreserveAspectFit
        }
    }
    decrementControl: Item {
        implicitWidth: padding.right
        Image {
            source: "../images/arrow_down.png"
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -2
            //opacity: control.enabled ? (styleData.downPressed ? 1 : 0.6) : 0.5
            width: 3 * Screen.pixelDensity
            fillMode: Image.PreserveAspectFit
        }
    }
}

