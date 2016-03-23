import QtQuick 2.0

import "WHDockAreas.js" as Areas

Rectangle {
    id: root

    default property alias content: centralPane.data
    property QtObject main: null

    function chooseArea(tx, ty) {
        if (tx < width / 4)
            return Areas.Left
        if (tx > width / 4 * 3)
            return Areas.Right
        if (ty < height / 4)
            return Areas.Top
        if (ty > height / 4 * 3)
            return Areas.Bottom

        return -1
    }

    function dockInto(area, item) {
        //Dock to specific area
        if (area === Areas.Left)
            item.anchors.right = undefined
        else
            item.anchors.right = root.right
        if (area === Areas.Top) {
            item.anchors.bottom = undefined
            item.height = height / 8
        } else
            item.anchors.bottom = root.bottom
        if (area === Areas.Right)
            item.anchors.left = undefined
        else
            item.anchors.left = root.left
        if (area === Areas.Bottom) {
            item.anchors.top = undefined
            item.height = height / 8
        } else
            item.anchors.top = root.top
    }

    function dockContent(area, item, content) {
        //Set content anchors
        if (area === Areas.Left)
            content.anchors.left = item.right
        else if (area === Areas.Top)
            content.anchors.top = item.bottom
        else if (area === Areas.Right)
            content.anchors.right = item.left
        else if (area === Areas.Bottom)
            content.anchors.bottom = item.top
    }

    function parentAnchor(area) {
        if (area === Areas.Left)
            return root.left
        else if (area === Areas.Top)
            return root.top
        else if (area === Areas.Right)
            return root.right
        else if (area === Areas.Bottom)
            return root.bottom
    }

    function dockAnchor(area, item) {
        if (area === Areas.Left)
            return item.anchors['left']
        else if (area === Areas.Top)
            return item.anchors.top
        else if (area === Areas.Right)
            return item.anchors.right
        else if (area === Areas.Bottom)
            return item.anchors.bottom
    }

    function dock(tx, ty, item) {
        var lx = tx - main.x
        var ly = ty - main.y

        var localCoord = mapToItem(root, lx, ly)

        //Qt.point(lx, ly)
        if (contains(localCoord)) {
            //Remove anchors
            item.anchors.fill = undefined

            //Set new parent
            item.parent = root

            var area = chooseArea(lx, ly)
            if (area === -1)
                return false

            dockInto(area, item)

            for (var i = 0; i < children.length; ++i) {
                var child = children[i]
                if (child === item)
                    continue

                if (dockAnchor(area, child) === parentAnchor(area))
                    dockContent(area, item, child)
            }

            return true
        }

        return false
    }

    function check(tx, ty) {
        var lx = tx - main.x
        var ly = ty - main.y

        var localCoord = mapToItem(root, lx, ly)

        //Qt.point(lx, ly)
        if (contains(localCoord))
            color = "green"
        else
            color = "transparent"
    }

    Item {
        id: centralPane
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
            bottom: parent.bottom
        }
    }
}

