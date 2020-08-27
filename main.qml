
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
    width: 640
    height: 480
    title: qsTr("Hello World")

    TableView {
        id: _tableView
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        interactive : false

        model: DatabaseModel{}

        function getRowData(index) {
            return _tableView.model.rows[Math.floor(index % (_tableView.rows)) - 1][Math.floor(index / (_tableView.rows))].toString()
        }

        function getHeaderData(index) {
            console.log(index)
            return _tableView.model.roles[Math.floor(index/(_tableView.rows))]
        }

        delegate: Rectangle {
            implicitHeight: 30
            implicitWidth: 200
            id: _delegate
            color: index % _tableView.rows === 0 ? "lightblue" : "green"
            Text {
                anchors.centerIn: _delegate
                text: index % _tableView.rows === 0 ? _tableView.getHeaderData(index) : _tableView.getRowData(index)
            }
        }
    }

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
