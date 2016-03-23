import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    id: splash

    property alias image: splashImage.source

    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen | Qt.FramelessWindowHint
    x: (Screen.width - width) / 2
    y: (Screen.height - height) / 2

    Image {
        id: splashImage
        anchors.fill: parent
    }
}
