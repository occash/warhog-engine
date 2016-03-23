import QtQuick 2.4
import QtQuick.Controls 1.2

import "style"

MenuBar {
    id: mainMenu
    style: WHMenuBarStyle {}

    Menu {
        title: qsTr("&FILE")

        MenuItem {
            text: qsTr("&New Project")
            shortcut: "Ctrl+N"
        }

        MenuItem {
            text: qsTr("&Open Project")
            shortcut: "Ctrl+O"
        }

        MenuItem {
            text: qsTr("&Close Project")
            //shortcut: "Ctrl+N"
        }

        MenuItem {
            text: qsTr("&Save Project")
            shortcut: "Ctrl+S"
        }

        MenuSeparator {}

        Menu {
            title: qsTr("&Recent Projects")
            visible: config.recent.length

            Component.onCompleted: {
                for (var i = 0; i < config.recent.length; ++i)
                    addItem(config.recent[i])
            }
        }

        MenuSeparator { visible: config.recent.length }

        MenuItem {
            text: qsTr("E&xit")
            shortcut: "Alt+F4"
            onTriggered: Qt.quit();
        }
    }

    Menu {
        title: qsTr("VIEW")

        MenuItem {
            text: qsTr("Scene view")
            //shortcut: "Ctrl+N"
        }

        MenuItem {
            text: qsTr("Resource view")
            //shortcut: "Ctrl+O"
        }

        MenuItem {
            text: qsTr("Inspector")
            //shortcut: "Ctrl+N"
        }
    }

    Menu {
        title: qsTr("ENTITY")

        MenuItem {
            text: qsTr("Create")
            //shortcut: "Ctrl+N"
        }
    }

    Menu {
        title: qsTr("COMPONENT")

        Menu {
            title: qsTr("Mesh")

            MenuItem {
                text: qsTr("Mesh Filter")
                //shortcut: "Ctrl+O"
            }

            MenuItem {
                text: qsTr("Material")
                //shortcut: "Ctrl+N"
            }
        }

        Menu {
            title: qsTr("Audio")

            MenuItem {
                text: qsTr("Listener")
                //shortcut: "Ctrl+O"
            }

            MenuItem {
                text: qsTr("Sound")
                //shortcut: "Ctrl+N"
            }
        }

        Menu {
            title: qsTr("Rendering")

            MenuItem {
                text: qsTr("Camera")
                //shortcut: "Ctrl+O"
            }

            MenuItem {
                text: qsTr("Light")
                //shortcut: "Ctrl+N"
            }
        }

        Menu {
            title: qsTr("Script")

            MenuItem {
                text: qsTr("Lua Script")
                //shortcut: "Ctrl+N"
            }
        }
    }

    Menu {
        title: qsTr("HELP")

        MenuItem {
            text: qsTr("About Warhog")
            //shortcut: "Ctrl+N"
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Warhog Manual")
            //shortcut: "Ctrl+O"
        }

        MenuItem {
            text: qsTr("Scripting Reference")
            //shortcut: "Ctrl+N"
        }
    }
}

