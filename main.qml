import QtQuick 2.15
import QtQuick.Controls 2.15
import MainWindowComponents 1.0

ApplicationWindow {
    id: _root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

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
            model: _main.model.tablesName

            TabButton {
                text: modelData
                width: implicitWidth
            }
        }

        onCurrentIndexChanged: {
            _main.model.changeTab(currentIndex)
            console.log("current index " + currentIndex)
        }
    }
}
