import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.3

import "."

ButtonStyle {
    background: Rectangle {
        id: button

        implicitWidth: 20 * Screen.pixelDensity
        implicitHeight: 5 * Screen.pixelDensity

        color: Style.button

        states: [
            State {
                name: "active"
                when: control.hovered || control.pressed
                PropertyChanges { target: button; color: Style.highlight }
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
        text: control.text
        clip: true
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.fill: parent
        color: Style.text
        font.weight: Font.DemiBold
        font.family: "Segoe UI"
        renderType: Text.NativeRendering
    }
}
