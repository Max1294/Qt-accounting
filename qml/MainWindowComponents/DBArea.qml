import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TableView {
//    anchors.fill: _tab1
    TableViewColumn {
        role: "title"
        title: "Title"
        width: _tab1.width / 2
    }
    TableViewColumn {
        role: "author"
        title: "Author"
        width: _tab1.width / 2
    }

    ListModel {
        id: libraryModel
        ListElement {
            title: "A Masterpiece"
            author: "Gabriel"
        }
        ListElement {
            title: "Brilliance"
            author: "Jens"
        }
        ListElement {
            title: "Outstanding"
            author: "Frederik"
        }
    } // ListModel

    alternatingRowColors: false
    model: libraryModel
    backgroundVisible: false

    style: TableViewStyle {
        // TODO: centerIn, backgroundColor
        headerDelegate: Text {
            text: styleData.value
            color: "green"
            font.pointSize: 8
        } // headerDelegate

        itemDelegate: Text {
            text: styleData.value
            color: "black"
            font.pointSize: 8
        } // itemDelegate: Text

        rowDelegate: Rectangle {
            id: _rowDeleg
            color: "lightsteelblue"
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                hoverEnabled: true

                // TODO: click -> open options: edir, delete, copy, paste
                onClicked: {
                    if(mouse.button === Qt.RightButton)
                        _flipMenu.popup()
                }

                onEntered: {
                    if(entered)
                        _rowDeleg.color = "green"
                }

                onExited: {
                    if(exited)
                        _rowDeleg.color = "lightsteelblue"
                }

                Menu {
                    id: _flipMenu
                    MenuItem {
                        text: qsTr("edit")
                    }
                    MenuItem {
                        text: qsTr("copy")
                    }
                    MenuItem {
                        text: qsTr("paste")
                    }
                    MenuItem {
                        text: qsTr("delete")
                    }
                } // Menu
            } // MouseArea
        } // rowDelegate: Rectangle
    } // TableViewStyle
} // TableView
