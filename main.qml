import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

import MainWindowComponents 1.0

ApplicationWindow {
    id: _root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MainArea {
        anchors.top: _menuBar.bottom
        anchors.fill: parent
    }

    menuBar: MenuBarArea {
        id: _menuBar
        width: _root.width
        height: Math.min(40, _root.height)
    }
}
