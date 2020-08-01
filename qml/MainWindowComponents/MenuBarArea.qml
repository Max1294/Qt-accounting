import QtQuick 2.0
import QtQuick.Window 2.15
import QtQuick.Controls 2.3

MenuBar {
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
}