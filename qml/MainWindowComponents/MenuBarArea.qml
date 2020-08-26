import QtQuick 2.15
import QtQuick.Controls 2.3

MenuBar {
       Menu {
        title: qsTr("&File")
        MenuBarItem {text: qsTr("Open database"); onTriggered: fileDialog.open()}
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
        title: qsTr("&Actions")
        MenuBarItem {text: "Add row"; onTriggered: __model.addRow()}
        MenuBarItem {text: "Add column"; onTriggered: __model.addColumn("NewColumn")}
    }
    Menu {
        title: qsTr("&Help")
    }
}
