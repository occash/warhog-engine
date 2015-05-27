import QtQuick 2.4
import QtQuick.Controls 1.2

import "../style"

ComboBox {
    id: editor
    property alias value: editor.model
    style: WHComboBoxStyle {}
}

