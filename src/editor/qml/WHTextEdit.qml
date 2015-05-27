import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2

Rectangle {
    anchors.fill: parent
    color: "#1e1e1e"

    Item {
        id: lineColumn
        width: column.width
        height: parent.height
        clip: true

        Column {
            id: column
            y: -textarea.flickableItem.contentY + 4
            width: metric.width + 5

            TextMetrics {
                id: metric
                text:  {
                    var n = textarea.lineCount.toString().length
                    return new Array(n + 1).join('0')
                }
                font.family: textarea.font
            }

            Repeater {
                model: textarea.lineCount
                delegate: Text {
                    color: "#e1e1e1"
                    font: textarea.font
                    width: lineColumn.width
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    renderType: Text.NativeRendering
                    text: index + 1
                }
            }
        }
    }

    TextArea {
        id: textarea

        anchors.left: lineColumn.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        wrapMode: TextEdit.NoWrap
        frameVisible: false

        style: TextAreaStyle {
            backgroundColor: "#1e1e1e"
            textColor: "#e1e1e1"
        }
    }
}
