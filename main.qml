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

    SplitView {
        anchors.top: _menuBar.bottom
        anchors.fill: parent
        Item {
            width: parent.width / 3
            Layout.minimumWidth: Math.min(100, _root.width * 0.3)
            TreeView{
                anchors.fill: parent
            }
        }
        Item{
             width: parent.width / 2
             Layout.maximumWidth: _root.width * 0.9
             Column {
                Repeater {
                    TableView{}
                }
             }
        }
    }

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
