import QtQuick 2.4

Item {
    WHSplash {
        id: splash

        width: 500
        height: 300

        image: "qrc:/splash"
        //visible: loader.status !== Loader.Ready
    }

    Loader {
        id: loader
        sourceComponent: MainWindow {}

        onStatusChanged: {
            if (status === Loader.Ready)
                splash.close()
        }
    }
}
