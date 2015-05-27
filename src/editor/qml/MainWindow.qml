import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.3

import Qt.labs.settings 1.0

//import Warhog 1.0

import "style"

WHMainWindow {
    id: main

    visible: true
    title: qsTr("Start Page - Warhog Editor")
    icon: "images/icon.png"//"qrc:/icon"

    width: config.width
    height: config.height
    visibility: config.visibility

    Settings {
        id: config
        category: "editor"

        property var recent: []
        property int visibility: Window.Windowed
        property int width: 640
        property int height: 480
    }

    onClosing: {
        config.visibility = visibility
        if (visibility === Window.Windowed) {
            config.width = width
            config.height = height
        }
    }

    menuBar: MainMenu {}

    ScenePane {
        id: scenePane
        title: qsTr("Scene")

        width: 200
        anchors {
            left: parent.left
            top: parent.top
            bottom: resourcePane.top
        }
    }

    Rectangle {
        id: central
        color: "black"
        clip: true

        anchors {
            left: scenePane.right
            right: inspectorPane.left
            top: parent.top
            bottom: resourcePane.top
        }

        Text {
            anchors.centerIn: parent
            text: "Preview not available"
            font.family: "Segoe UI"
            font.pixelSize: 24
            color: Style.text
        }
    }

    InspectorPane {
        id: inspectorPane
        title: qsTr("Inspector")

        width: 200
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
    }

    ResourcePane {
        id: resourcePane
        title: qsTr("Resources")

        height: 200
        anchors {
            left: parent.left
            right: inspectorPane.left
            bottom: parent.bottom
        }
    }

    /*WHTextEdit {
        anchors.fill: parent
    }*/

    /*function createDock() {
        var dockPane = paneComponent.createObject()
        rectComponent.createObject(dockPane.content)
    }

    WHDockArea {
        id: root
        anchors.fill: parent
        color: "transparent"
        main: mainWindow

        WHTextEdit {
            id: textEdit
            anchors.fill: parent
        }
    }

    Component {
        id: paneComponent
        WHDockPane {
            dockArea: root
        }
    }

    Component {
        id: rectComponent
        Rectangle {
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1)
            anchors.fill: parent
        }
    }

    Component.onCompleted: {
        createDock()
        createDock()
        createDock()
        createDock()
    }*/
}
