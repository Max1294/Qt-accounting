import QtQuick 2.15
import QtQuick.Controls 2.15
import MainWindowComponents 1.0

ApplicationWindow {
    id: _root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//    Loader {
//        id: _loader
//        anchors.fill: parent

//        Component.onCompleted: setSource("DBArea.qml", {"id": _main,
//                                             "anchors.top": _menuBar.bottom,
//                                             "anchors.bottom": _tabBar.top,
//                                             "anchors.fill": parent})
//        //        source: qsTr("qrc:/qml/MainWindowComponents/DBArea.qml")
//    }

//    MouseArea {
//        anchors.fill: parent

//        onClicked: {
//            if(clicked) {
//                _loader.setSource("qrc:/qml/MainWindowComponents/DBArea.qml",
//                                      {"id": _main,
//                                      "anchors.top": _menuBar.bottom,
//                                      "anchors.bottom": _tabBar.top,
//                                      "anchors.fill": parent})
//            }
//        }
//    }

    DBArea {
        id: _main
        anchors.top: _menuBar.bottom
        anchors.bottom: _tabBar.top
        anchors.fill: parent
    }

    menuBar: MenuBarArea {
        id: _menuBar
        width: _root.width
        height: Math.min(40, _root.height)
    }

    footer: TabBar {
        id: _tabBar
        width: _root.width

        Repeater {
            id: _repeater
            model: _main._model.tablesName
            TabButton {
                text: modelData
                width: implicitWidth

                background: Rectangle {
                    id: _tabBachground
                    color: "#469c9b"
                }
            }
        }

        background: Rectangle {
            color: "grey"
        }

        onCurrentIndexChanged: {
            _main._model.setTab(currentIndex)
            console.log("current index " + currentIndex)
        }
    }
}
