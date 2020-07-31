import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: _root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

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
    }


    SplitView {
        anchors.top: _menuBar.bottom
        anchors.fill: parent

        Item {
            id: _parentItem
            width: parent.width / 3
            Layout.minimumWidth: Math.min(100, _root.width * 0.3)
            Layout.maximumWidth: _root.width * 0.7
            TreeView {
                anchors.fill: parent
            } // TreeView
        } // Item

        Item {
            id: _mainArea
             width: parent.width / 2
             Layout.maximumWidth: _root.width * 0.9
             Column {
                Repeater {
                    model: 1
                    TabView
                    {
                        id: _tabView
                        width: _root.width - _parentItem.width
                        height: _root.height - _menuBar.height

                        Tab {
                            id: _tab1
                            width: _tabView.width
                            height: _tabView.height
                            title: "tab_1"

                            TableView{
                                anchors.fill: _tab1

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
                                model: libraryModel
                            } // TableView
                        } // Tab

                        Tab {
                            id: _tab2
                            title: "tab_2"

                            Rectangle {
                                width: _tab2.width
                                height: _tab2.height
                                color: "green"
                            } // Rectangle
                        } // Tab
                    } // TabView
                } // Repeater
             } // Column
        } // Item
    } // SplitView

    menuBar: MenuBar {
        id: _menuBar
        width: _root.width
        height: Math.min(40, _root.height)
       Menu {
        title: qsTr("&File")
        Action {text: qsTr("New database")}
        Action {text: qsTr("New table")}
        MenuSeparator { }
        Action {text: qsTr("Exit")}
    }

    Menu {
        title: qsTr("&Import/Export")
        Action {text: qsTr("Import database")}
        Action {text: qsTr("Export database")}
    }
    Menu {
        title: qsTr("&Help")
    }

    } // MenuBar

}
