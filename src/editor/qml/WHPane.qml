import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.0

import "style"

Rectangle {
    id: pane

    default property alias data: content.data
    property alias title: titleText.text

    color: Style.base

    Rectangle {
        id: titleBar

        color: Style.highlight

        height: 6 * Screen.pixelDensity
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
        }

        Text {
            id: titleText
            anchors {
                left: parent.left
                top: parent.top
                right: titleButtons.left
                bottom: parent.bottom
                leftMargin: 3 * Screen.pixelDensity
            }

            color: Style.text
            horizontalAlignment: Qt.AlignLeft
            verticalAlignment: Qt.AlignVCenter
            renderType: Text.NativeRendering
            font.pointSize: 9
            font.family: "Segoe UI"
        }

        Row {
            id: titleButtons
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }

            Button {
                id: closeButton
                width: height
                height: parent.height
                iconSource: "images/close.png"
                style: ButtonStyle {
                    background: Rectangle {
                        color: control.pressed ?
                                   Style.dark : control.hovered ?
                                       Style.mid : "transparent"
                    }
                    label: Item {
                        Image {
                            anchors.centerIn: parent
                            source: control.iconSource
                            smooth: false
                        }
                    }
                }
                onClicked: pane.visible = false
            }
        }

        /*MouseArea {
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
        }*/
    }

    Item {
        id: content
        clip: true

        anchors {
            left: parent.left
            top: titleBar.bottom
            right: parent.right
            bottom: parent.bottom
        }
    }
}
