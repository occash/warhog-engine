import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

import "style"

ApplicationWindow {
    id: window

    color: "transparent"

    property string icon: ""
    property Item titleBar: WHTitleBar {
        target: window
        icon: window.icon
        title: window.title
        maximized: window.visibility === Window.Maximized

        height: 10 * Screen.pixelDensity
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
        }

        onMinimize: window.showMinimized()
        onMaximize: toggleMaximized()
        onClose: window.close()
    }

    style: WHWindowStyle {
        frameWidth: 5
        background: Rectangle {
            anchors.fill: parent
            color: Style.base
        }
        frame: WHSizeGrip {
            anchors.fill: parent
            target: window
            gripSize: frameWidth
            allowed: window.visibility === Window.Windowed

            Rectangle {
                id: borderRect
                anchors.fill: parent
                anchors.margins: frameWidth - 1
                border.color: window.active ? Style.highlight : Style.button
                border.width: window.visibility == Window.Maximized ||
                              window.visibility == Window.FullScreen ? 0 : 1
            }

            RectangularGlow {
                anchors.fill: borderRect
                glowRadius: 3
                spread: 0.0
                property color base: borderRect.border.color
                color: Qt.rgba(base.r, base.g, base.b, 0.5)
            }
        }
    }
    flags: Qt.FramelessWindowHint |
           Qt.Window

    function toggleMaximized() {
        if (window.visibility === Window.Maximized)
            window.visibility = Window.Windowed
        else
            window.visibility = Window.Maximized
    }

    Binding { target: titleBar; property: "parent"; value: __panel.titleBarArea }
}
