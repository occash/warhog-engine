import QtQuick 2.4
import QtQuick.Controls 1.2

import "../style"

CheckBox {
    id: editor
    property alias value: editor.checked
    style: WHCheckBoxStyle {}
}

