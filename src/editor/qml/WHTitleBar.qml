import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.0

import "style"

Item {
    id: titleBar

    property QtObject target: null
    property alias icon: titleIcon.source
    property alias title: titleText.text
    property bool maximized: false

    signal minimize()
    signal maximize()
    signal close()

    Image {
        id: titleIcon
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom

            margins: 1 * Screen.pixelDensity
            leftMargin: 3 * Screen.pixelDensity
        }

        source: ""
        fillMode: Image.PreserveAspectFit
        antialiasing: true
    }

    Text {
        id: titleText
        anchors {
            left: titleIcon.right
            top: parent.top
            right: titleButtons.left
            bottom: parent.bottom
            leftMargin: 3 * Screen.pixelDensity
        }

        color: Style.text
        horizontalAlignment: Qt.AlignLeft
        verticalAlignment: Qt.AlignVCenter
        renderType: Text.NativeRendering
        font.pointSize: 11
        font.family: "Segoe UI"

        MouseArea {
            id: titleDrag
            anchors.fill: parent

            property bool dragging: false
            property point clickPos: Qt.point(0, 0)

            onPressed: {
                dragging = true
                clickPos = Qt.point(mouse.x, mouse.y)
            }

            onReleased: {
                dragging = false
            }

            onPositionChanged: {
                if (dragging) {
                    if (maximized) {
                        var globalX = target.x + mouse.x
                        var globalY = target.y + mouse.y

                        maximize()

                        target.x = globalX - target.width / 2
                        target.y = globalY - titleBar.height / 2

                        clickPos.x = target.width / 2
                        clickPos.y = titleBar.height / 2

                        return
                    }

                    var deltaX = mouse.x - clickPos.x
                    var deltaY = mouse.y - clickPos.y
                    target.x += deltaX
                    target.y += deltaY
                }
            }

            onDoubleClicked: maximize()
        }
    }

    Row {
        id: titleButtons
        anchors {
            right: parent.right
            top: parent.top
        }
        height: 7 * Screen.pixelDensity

        Button {
            id: minimizeButton
            width: 10 * Screen.pixelDensity
            height: parent.height
            iconSource: "images/minimize.png"
            style: WHBarButtonStyle {}
            onClicked: minimize()
        }

        Button {
            id: maximizeButton
            width: 10 * Screen.pixelDensity
            height: parent.height
            iconSource: maximized ?
                            "images/restore.png" :
                            "images/maximize.png"
            style: WHBarButtonStyle {}
            onClicked: maximize()
        }

        Button {
            id: closeButton
            width: 10 * Screen.pixelDensity
            height: parent.height
            iconSource: "images/close.png"
            style: WHBarButtonStyle {}
            onClicked: close()
        }
    }
}

