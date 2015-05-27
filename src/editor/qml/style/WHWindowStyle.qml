import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.3

import "."

ApplicationWindowStyle {
    property int frameWidth: 0
    property Component frame: Item {}
    panel: Item {
        readonly property alias contentArea: contentArea
        readonly property alias titleBarArea: titleBarArea
        readonly property alias menuBarArea: menuBarArea
        readonly property alias toolBarArea: toolBarArea
        readonly property alias statusBarArea: statusBarArea

        Loader {
            anchors.fill: parent
            sourceComponent: frame
        }

        Item {
            anchors.fill: parent
            anchors.margins: control.visibility === Window.Windowed
                             ? frameWidth : 0

            Loader {
                anchors.fill: parent
                sourceComponent: background
            }

            Item {
                id: contentArea
                anchors.top: toolBarArea.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: statusBarArea.top
            }

            Item {
                id: titleBarArea
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                implicitHeight: childrenRect.height
                height: visibleChildren.length > 0 ? implicitHeight: 0
                clip: true
            }

            Item {
                id: toolBarArea
                anchors.top: menuBarArea.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                implicitHeight: childrenRect.height
                height: visibleChildren.length > 0 ? implicitHeight: 0
                clip: true
            }

            Item {
                id: menuBarArea
                anchors.top: titleBarArea.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                implicitHeight: childrenRect.height
                height: visibleChildren.length > 0 ? implicitHeight: 0
                clip: true
            }

            Item {
                id: statusBarArea
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                implicitHeight: childrenRect.height
                height: visibleChildren.length > 0 ? implicitHeight: 0
                clip: true
            }
        }
    }
}

