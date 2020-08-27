import QtQuick 2.15
import TableModel 1.0
import QtQuick.Controls 2.15

Rectangle {
    id: _root
    property alias _model: _tableView.model

    color: "grey"

    VerticalHeaderView {
        id: _verticalHeader
        implicitWidth: 30
        height: _root.height
        interactive: false
        rowSpacing: 1

        model: _tableView.rows + 1

        delegate: Rectangle {
            id: _verticalHeaderDelegate
            implicitHeight: index === 0 ? 61 : 30
            implicitWidth: 30
            color: "lightblue"


            // TODO make button or mouse area to delete row
            Button {
                width: index === 0 ? 0 : 17
                height: index === 0 ? 0 : 30
                text: "x"
                anchors.right: _verticalHeaderDelegate.right
                anchors.top: _verticalHeaderDelegate.top

                onClicked: {
                    console.log("delete row")
                    _model.deleteRow(index-1)
                }
            }

            Text {
                anchors.centerIn: _verticalHeaderDelegate
                text: index === 0 ? "№" : index
            } // Text
        } // delegate
    } // VerticalHeaderView

    HorizontalHeaderView {
        id: _horizontalHeader
        anchors.left: _tableView.left
        implicitWidth: _root.width
        height: 30
        syncView: _tableView
        interactive : false
        columnSpacing: 1
        rowSpacing: 1

        delegate: Column {
            spacing: 1
            Rectangle {
                id: _horizontalHeaderDelegate
                implicitHeight: _horizontalHeader.height
                implicitWidth: Math.max(_horizontalHeaderText.contentWidth + 10, _tableView.width / _tableView.columns)
                color: "lightblue"
                Text {
                    id: _horizontalHeaderText
                    text: display
                    anchors.centerIn: _horizontalHeaderDelegate
                }

                Button {
                    id: _closeButton
                    width: 20
                    height: 30
                    text: "x"
                    anchors.right: _horizontalHeaderDelegate.right

                    onClicked: {
                        _model.deleteColumn(index)
                        console.log("delete column")
                    }
                }

                MouseArea {
                    id: _headerMouseArea
//                    anchors.fill: parent
                    width: _horizontalHeaderDelegate.width - 20
                    height: 30
                    hoverEnabled: true

                    onClicked: {
                        if(mouse.button === Qt.LeftButton)
                        {
                            _tableView.model.sortColumn(index, "order")
                        }
                    }
                } // MouseArea
            } // Rectangle

            TextArea {
                implicitHeight: 30
                implicitWidth:  _horizontalHeaderDelegate.implicitWidth
                background: Rectangle {color: "yellow"}
                placeholderText: "filter"
                text: _tableView.model.tablesFieldsFilter(_horizontalHeaderText.text)

                onEditingFinished: {
                    _tableView.model.sortColumn(index, text)
                }
            } // TextArea
        } // delegate
    } // HorizontalHeaderView

    TableView {
        id: _tableView
        width: _root.width - 30
        height: _root.height - 50
        anchors.top: _horizontalHeader.bottom
        anchors.left: _verticalHeader.right
        anchors.topMargin: 32
        anchors.leftMargin: 1
        columnSpacing: 1
        rowSpacing: 1
        interactive : false

        model: DatabaseModel{}

        delegate: Rectangle {
            id: _tableViewDelegate
            implicitHeight: 30
            implicitWidth: Math.max(_tableViewText.contentWidth + 10, _tableView.width / _tableView.columns)
            color: "green"
            TextEdit {
                id: _tableViewText
                anchors.centerIn: _tableViewDelegate
                text: display === "" ? "NULL" : display

                onEditingFinished: {
                    _tableView.model.editField(index, _tableViewText.text)
                }
            } // TextEdit
        } // Delegate
    } // TableView
} // Item
