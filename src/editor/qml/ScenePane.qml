import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.2

import "style"

WHPane {
    id: pane

    TextField {
        id: searchBox
        style: WHTextFieldStyle {}
        placeholderText: qsTr("Search entity")

        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
            topMargin: 1
        }

        Image {
            source: "images/search.png"
            width: height

            anchors {
                top: parent.top
                right: parent.right
                bottom: parent.bottom
            }
        }
    }

    ListView {
        id: view

        anchors {
            left: parent.left
            top: searchBox.bottom
            right: parent.right
            bottom: parent.bottom
            topMargin: 1
        }

        clip: true
        boundsBehavior: Flickable.StopAtBounds
        highlightRangeMode: ListView.ApplyRange
        highlightFollowsCurrentItem: true
        highlightMoveDuration: 0

        currentIndex: 0

        model: sceneModel
        delegate: Item  {
            height: 5 * Screen.pixelDensity
            width: view.width
            clip: true

            Text {
                anchors.fill: parent
                anchors.leftMargin: 3 * Screen.pixelDensity
                color: Style.text
                text: display
                renderType: Text.NativeRendering
            }

            MouseArea {
                anchors.fill: parent
                onPressed: view.currentIndex = index
            }
        }
        highlight: Rectangle {
            color: Style.highlight
        }
    }
}
