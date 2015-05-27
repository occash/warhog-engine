import QtQuick 2.4
import QtGraphicalEffects 1.0
import Qt.labs.folderlistmodel 2.1

import "style"

WHPane {
    id: pane

    FolderListModel {
        id: folderModel
        showDirsFirst: true
        nameFilters: ["*.qml"]
    }

    GridView {
        id: view

        anchors.fill: parent
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

