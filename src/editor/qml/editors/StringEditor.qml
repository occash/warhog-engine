import QtQuick 2.4
import QtQuick.Controls 1.2

import "../style"

TextField {
    id: editor
    property alias value: editor.text
    style: WHTextFieldStyle {}
}

