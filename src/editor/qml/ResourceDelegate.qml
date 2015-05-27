import QtQuick 2.4

import "style"

Item {
    id: resource

    property alias name: name.text
    property bool group: false

    signal clicked(string name)

    Image {
        id: icon
        width: resource.width * 0.75
        height: resource.height * 0.75

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10

        source: group ? "images/folder.png" : "images/icon.png"
        smooth: true
    }

    Text {
        id: name

        anchors.bottom: parent.bottom
        anchors.top: icon.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.margins: 10

        color: Style.text
        font.family: "Segoe UI"
        //wrapMode: Text.WrapAnywhere
        elide: Text.ElideMiddle
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 10
        renderType: Text.NativeRendering
    }

    MouseArea {
        anchors.fill: parent
        enabled: group
        onClicked: resource.clicked(resource.name)
    }
}

