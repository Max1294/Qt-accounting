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

        delegate: Rectangle{
            id: _headerDelegate
            implicitHeight: _header.height
            implicitWidth: Math.max(_headerText.contentWidth + 10, _tableView.width / _tableView.columns)
            color: "lightblue"
            Text {
                id: _headerText
                text: display
                anchors.centerIn: _headerDelegate
            }

            MouseArea {
                id: _headerMouseArea
                anchors.fill: parent
                hoverEnabled: true

//                onEntered: {
//                    _headerText.text = "sorted"
//                }

                onClicked: {
                    if(mouse.button === Qt.LeftButton)
                    {
                        _tableView.model.sortColumn(index)
                    }
                }
            }
        }
    }

    TableView {
        id: _tableView
        width: _root.width
        height: _root.height - 50
        anchors.top: _header.bottom
        columnSpacing: 1
        rowSpacing: 1
        interactive : false

        model: DatabaseModel{}

        delegate: Rectangle {
            id: _delegate
            implicitHeight: 30
            implicitWidth: Math.max(_text.contentWidth + 10, _tableView.width / _tableView.columns)
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
