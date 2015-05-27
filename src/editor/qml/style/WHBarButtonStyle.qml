import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.3

import "."

ButtonStyle {
    background: Rectangle {
        color: control.pressed ?
                   Style.highlight : control.hovered ?
                       Style.button : Style.base
    }
    label: Item {
        Image {
            anchors.centerIn: parent
            source: control.iconSource
            smooth: false
        }
    }
}

