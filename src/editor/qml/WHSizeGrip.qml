import QtQuick 2.3
import QtQuick.Window 2.0

MouseArea {
    id: sizeGrip

    property QtObject target: null
    property int gripSize: 5
    property bool allowed: true

    //private
    property bool resizing: false
    property int resizeWidth: 0
    property int resizeHeight: 0
    property point clickPos: Qt.point(0, 0)

    hoverEnabled: true
    propagateComposedEvents: true

    cursorShape: {
        if (!allowed)
            return Qt.ArrowCursor

        if (mouseX < gripSize || mouseX > width - gripSize)
            if ((mouseX < gripSize && mouseY < gripSize) ||
                    (mouseX > width - gripSize &&
                     mouseY > height - gripSize))
                return Qt.SizeFDiagCursor
            else if ((mouseX < gripSize && mouseY > height - gripSize) ||
                     (mouseX > width - gripSize && mouseY < gripSize))
                return Qt.SizeBDiagCursor
            else
                return Qt.SizeHorCursor
        else if (mouseY < gripSize || mouseY > height - gripSize)
            return Qt.SizeVerCursor

        return Qt.ArrowCursor
    }

    onPressed: {
        if (!allowed) {
            mouse.accepted = false
            return
        }

        if (mouse.x < gripSize || mouse.x > width - gripSize) {
            resizing = true
            resizeWidth = width / 2 - mouse.x
        }
        if (mouse.y < gripSize || mouse.y > height - gripSize) {
            resizing = true
            resizeHeight = height / 2 - mouse.y
        }

        if (resizing)
            clickPos = Qt.point(mouse.x, mouse.y)
        else
            mouse.accepted = false
    }

    onReleased: {
        resizing = false
        resizeWidth = 0
        resizeHeight = 0
    }

    onPositionChanged: {
        if (resizing) {
            var deltaX = mouse.x - clickPos.x
            var deltaY = mouse.y - clickPos.y

            if (resizeWidth > 0) {
                target.x += deltaX
                target.width -= deltaX
            } else if (resizeWidth < 0) {
                target.width = mouse.x
            }

            if (resizeHeight > 0) {
                target.y += deltaY
                target.height -= deltaY
            } else if (resizeHeight < 0)
                target.height = mouse.y
        }

        mouse.accepted = false
    }
}

