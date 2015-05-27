import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2

import "."

ComboBoxStyle {
    property bool dark: true
    property WHTheme palette: dark ? Style.dark : Style.light

    textColor: palette.text
    selectedTextColor: palette.text
    selectionColor: palette.highlight
    dropDownButtonWidth: 5 * Screen.pixelDensity
    background: Rectangle {
        id: button

        implicitWidth: 20 * Screen.pixelDensity
        implicitHeight: 5 * Screen.pixelDensity

        color: palette.button

        Image {
            id: imageItem
            visible: control.menu !== null
            source: "qrc:/images/icons/arrow_down.png"
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
                PropertyChanges { target: button; color: palette.highlight }
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
        color: Style.textColor
        //font.weight: Font.DemiBold
    }

    __dropDownStyle: MenuStyle {
        //font: cbStyle.font
        __labelColor: Style.textColor
        __selectedLabelColor: Style.textColor
        __selectedBackgroundColor: Style.selectionColor
        __backgroundColor: Style.secondColor
        __borderColor: Style.secondColor
        __maxPopupHeight: 600
        __menuItemType: "comboboxitem"
        __scrollerStyle: ScrollViewStyle { }
        itemDelegate.background: Rectangle {
            visible: styleData.selected && styleData.enabled
            color: Style.selectionColor
            antialiasing: true
        }
    }
}

