import QtQuick 2.15
import TableModel 1.0

TableView {
    id: _tableView
    columnSpacing: 1
    rowSpacing: 1
    interactive : false

    model: DatabaseModel{}

    delegate: Rectangle {
        implicitHeight: 30
        implicitWidth: Math.max(_text.contentWidth + 10, _tableView.width / columns)
        id: _delegate
        color: "green"
        TextEdit {
            id: _text
            anchors.centerIn: _delegate
            text: display

            onEditingFinished: {
                _tableView.model.editField(index, _text.text)
                console.log("edited " + _text.text)
            }
        } // TextEdit
    } // Delegate
} // TableView
