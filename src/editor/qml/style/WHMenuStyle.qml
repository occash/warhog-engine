import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2

import "."

MenuStyle {
    frame: Rectangle {
        color: Style.alternateBase
    }
    separator: Item {
        implicitHeight: 1 * Screen.pixelDensity
        Rectangle {
            width: parent.width - __leftLabelMargin
            height: 1
            x: __leftLabelMargin - 1 * Screen.pixelDensity
            anchors.verticalCenter: parent.verticalCenter
            color: Style.base
        }
    }
    itemDelegate.background: Rectangle {
        color: (styleData.selected && styleData.enabled) ? Style.button : "transparent"
        antialiasing: true

        Item {
            id: icon
            height: parent.height
            width: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter

            Image {
                anchors.fill: parent
                anchors.margins: 2
                source: styleData.iconSource ? styleData.iconSource : ""
                fillMode: Image.PreserveAspectFit
            }
        }
    }
    itemDelegate.label: Text {
        id: text
        color: Style.text
        text: formatMnemonic(styleData.text, styleData.underlineMnemonic)
        font.family: "Segoe UI"
        font.pointSize: 10
        renderType: Text.NativeRendering
        verticalAlignment: Text.AlignVCenter
    }
    itemDelegate.shortcut: Text {
       text: styleData.shortcut
       font.family: "Segoe UI"
       font.pointSize: 10
       color: Style.text
       renderType: Text.NativeRendering
   }
    __leftLabelMargin: 30
}

