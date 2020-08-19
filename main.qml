
import QtQuick.Window 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15
import MainWindowComponents 1.0
import QtQuick 2.15

import QtQuick.Controls.Styles 1.4
import TableModel 1.0

ApplicationWindow {
    id: _root
    visible: true
    width: Math.max(640, _tableView.width)
    height: 480
    title: qsTr("Hello World")

    TableView {
        id: _tableView
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        interactive : false

        model: DatabaseModel{}

        delegate: Rectangle {
            implicitHeight: 30
            implicitWidth: _text.contentWidth + 10
            id: _delegate
            color: index % _tableView.rows === 0 ? "lightblue" : "green"
            Text {
                id: _text
                anchors.centerIn: _delegate
                text: Name
            }
        } // delegate

        Component.onCompleted:
        {
//            console.log(_tableView.model.roles[0].toString())
        }
    } // TableView

//    MainArea {
//        anchors.top: _menuBar.bottom
//        anchors.fill: parent
//    }

//    menuBar: MenuBarArea {
//        id: _menuBar
//        width: _root.width
//        height: Math.min(40, _root.height)
//    }
}
