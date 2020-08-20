import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import TableModel 1.0

TableView {
    id: _tableView
    columnSpacing: 1
    rowSpacing: 1
    interactive : false
    property alias mainModel: _tableView.model
    model: DatabaseModel{}

    delegate: Rectangle {
        implicitHeight: 30
        implicitWidth: _text.contentWidth + 10
        id: _delegate
        color: "green"
        Text {
            id: _text
            anchors.centerIn: _delegate
            text: display
        }
    } // delegate
} // TableView
