import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2

import "."

ComboBoxStyle {
    textColor: Style.text
    selectedTextColor: Style.text
    selectionColor: Style.highlight
    dropDownButtonWidth: 5 * Screen.pixelDensity
    background: Rectangle {
        id: button

        implicitWidth: 20 * Screen.pixelDensity
        implicitHeight: 5 * Screen.pixelDensity

        color: Style.button

        Image {
            id: imageItem
            visible: control.menu !== null
            source: "../images/arrow_down.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 2 * Screen.pixelDensity
            //opacity: control.enabled ? 0.6 : 0.3
            width: 3 * Screen.pixelDensity
            fillMode: Image.PreserveAspectFit
        }

        states: [
            State {
                name: "active"
                when: control.hovered || control.pressed
                PropertyChanges { target: button; color: Style.highlight }
            }
        ]

        transitions: [
            Transition {
                to: ""
                ColorAnimation { property: "color" }
            },
            Transition {
                to: "active"
                ColorAnimation { property: "color" }
            }
        ]
    }

    label: Text {
        text: control.currentText
        clip: true
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        //horizontalAlignment: Text.AlignHCenter
        anchors.fill: parent
        color: Style.text
        //font.weight: Font.DemiBold
    }

    __dropDownStyle: MenuStyle {
        //font: cbStyle.font
        __labelColor: Style.text
        __selectedLabelColor: Style.text
        __selectedBackgroundColor: Style.highlight
        __backgroundColor: Style.alternateBase
        __borderColor: Style.alternateBase
        __maxPopupHeight: 600
        __menuItemType: "comboboxitem"
        __scrollerStyle: ScrollViewStyle { }
        itemDelegate.background: Rectangle {
            visible: styleData.selected && styleData.enabled
            color: Style.highlight
            antialiasing: true
        }
    }
}

