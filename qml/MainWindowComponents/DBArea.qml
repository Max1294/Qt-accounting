import QtQuick 2.15
import TableModel 1.0
import QtQuick.Controls 2.15

Item {
    id: _root
    property alias _model:_tableView.model
    HorizontalHeaderView{
        id: _header
        anchors.left: _tableView.left
        implicitWidth: _root.width
        height: 50
        syncView: _tableView
    }

    TableView {
        anchors.top: _header.bottom
        id: _tableView
        width: _root.width
        height: _root.height - 50
        columnSpacing: 1
        rowSpacing: 1
        interactive : false

        model: DatabaseModel{}

        delegate: Rectangle {
            implicitHeight: 30
            implicitWidth: Math.max(_text.contentWidth + 10, _tableView.width / _tableView.columns)
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
} // Item
