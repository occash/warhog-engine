import QtQuick 2.4
import QtQuick.Window 2.0

import "style"

WHPane {
    id: pane

    ListModel {
        id: componentModel
        dynamicRoles: true

        Component.onCompleted: {
            componentModel.append({
                "editor": "NumberEditor",
                "name": "Duration",
                "value": 11.0
            })

            componentModel.append({
                "editor": "StringEditor",
                "name": "Description",
                "value": "Light properties"
            })

            componentModel.append({
                "editor": "NumberEditor",
                "name": "Intensity",
                "value": 20.0
            })

            componentModel.append({
                "editor": "BoolEditor",
                "name": "Enable",
                "value": false
            })

            componentModel.append({
                "editor": "ListEditor",
                "name": "Flags",
                "value": [1, 2, 3]
            })
        }
    }

    ListView {
        id: view

        anchors.fill: parent
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        model: componentModel
        delegate: Item  {
            height: 7 * Screen.pixelDensity
            width: view.width
            clip: true

            Item {
                anchors.fill: parent
                anchors.margins: 0.5 * Screen.pixelDensity

                Text {
                    id: nameText

                    width: 20 * Screen.pixelDensity
                    anchors {
                        left: parent.left
                        top: parent.top
                        bottom: parent.bottom
                        leftMargin: 3 * Screen.pixelDensity
                    }

                    verticalAlignment: Text.AlignVCenter

                    color: Style.text
                    text: name
                    renderType: Text.NativeRendering
                }

                Loader {
                    id: loader
                    source: "editors/" + editor + ".qml"

                    anchors {
                        left: nameText.right
                        top: parent.top
                        right: parent.right
                        bottom: parent.bottom
                    }

                    Binding {
                        when: loader.status == Loader.Ready
                        target: loader.item
                        property: "value"
                        value: model.value
                    }
                }
            }
        }
    }
}
