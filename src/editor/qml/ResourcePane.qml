import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import Qt.labs.folderlistmodel 2.1

import "style"

WHPane {
    id: pane

    property string rootPath: "file:///C:/Windows"
    property string path: "/"
    property var pathModel: {
        var plist = path.split('/')
        plist = plist.filter(function(n){
            return n.length > 0
        })
        return plist
    }

    FolderListModel {
        id: folderModel
        showDirsFirst: true
        rootFolder: rootPath
        folder: rootPath + path
    }

    Item {
        id: pathBar
        clip: true

        height: 7 * Screen.pixelDensity
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
        }

        Row {
            anchors.fill: parent

            Repeater {
                model: pathModel

                Button {
                    height: pathBar.height
                    text: modelData
                    style: WHButtonStyle {}
                }
            }
        }
    }

    GridView {
        id: view

        anchors {
            left: parent.left
            top: pathBar.bottom
            right: parent.right
            bottom: parent.bottom
        }

        clip: true
        boundsBehavior: Flickable.StopAtBounds
        highlightRangeMode: GridView.ApplyRange
        highlightFollowsCurrentItem: true
        highlightMoveDuration: 0

        cellWidth: 70
        cellHeight: 70

        model: folderModel
        delegate: ResourceDelegate {
            width: view.cellWidth
            height: view.cellHeight
            name: fileBaseName
            group: fileIsDir

            onClicked: {
                var newPath = path + fileBaseName + "/"
                pane.path = newPath
            }
        }

        visible: !dropArea.containsDrag
    }

    Item {
        anchors.fill: parent

        GaussianBlur {
            anchors.fill: parent
            source: view
            radius: 8
            samples: 16
            visible: dropArea.containsDrag
        }

        Rectangle {
            anchors.fill: parent
            color: Style.base
            opacity: dropArea.containsDrag ? 0.2 : 0
        }

        Text {
            anchors.centerIn: parent

            opacity: dropArea.containsDrag ? 1 : 0
            color: Style.text
            text: qsTr("Ready to Import")

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            renderType: Text.NativeRendering

            font.family: "Segoe UI"
            font.pixelSize: 20
        }
    }

    DropArea {
        id: dropArea
        anchors.fill: parent
    }
}

