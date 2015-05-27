import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    id: dockPane

    default property alias data: content.data

    property alias content: content
    property WHDockArea dockArea: null

    width: 200
    height: 400

    flags: Qt.FramelessWindowHint
    visible: true

    Item {
        id: titleBar

        height: 5 * Screen.pixelDensity
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
        }

        MouseArea {
            id: area
            anchors.fill: parent

            property bool moving: false
            property int clickX: -1
            property int clickY: -1
            property int dockX: dockPane.x + mouseX
            property int dockY: dockPane.y + mouseY

            onPressed: {
                moving = true

                clickX = mouse.x
                clickY = mouse.y

                dockArea.check(dockX, dockY)
            }

            onReleased: {
                moving = false

                var result = dockArea.dock(dockX, dockY, content.children[0])
                if (result) {
                    dockPane.visible = false
                    dockArea.check(-1, -1)
                    destroy()
                }

                dockArea.check(-1, -1)
            }

            onPositionChanged: {
                if (moving) {
                    var deltaX = mouse.x - clickX
                    var deltaY = mouse.y - clickY

                    dockPane.x += deltaX
                    dockPane.y += deltaY

                    dockArea.check(dockX, dockY)
                }
            }
        }
    }

    Item {
        id: content
        anchors {
            left: parent.left
            top: titleBar.bottom
            right: parent.right
            bottom: parent.bottom
        }
    }
}

