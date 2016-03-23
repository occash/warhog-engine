import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2
//import QtQuick.Controls.Private 1.0

import "."

MenuBarStyle {
    padding.left: 2
    background: Item {
        implicitHeight: 5 * Screen.pixelDensity
    }
    itemDelegate: Rectangle {
        implicitWidth: text.width + 12
        implicitHeight: text.height
        color: styleData.open ?
                   Style.alternateBase :
                   styleData.selected ?
                   Style.button : Style.base

        Text {
            id: text
            text: formatMnemonic(styleData.text, styleData.underlineMnemonic)
            anchors.centerIn: parent
            renderType: /*Settings.isMobile ? Text.QtRendering : */Text.NativeRendering
            color: Style.text
            font.family: "Segoe UI"
            font.pointSize: 10
        }
    }
    menuStyle: WHMenuStyle {}
}
