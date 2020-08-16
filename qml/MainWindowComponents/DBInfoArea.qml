import QtQuick 2.0
import QtQuick.Controls 1.4
import TreeViewModel 1.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4

TreeView {
    backgroundVisible: false
    headerVisible: false

    TableViewColumn{
        width: parent.width
        role: "display"
        title: "Elements"
    }

    model: TreeViewModel{}

    rowDelegate: Rectangle{
        id: _rowDelegate
        anchors.fill: parent
        color: "black"
    }

    itemDelegate: CheckBox {
        id: control
        indicator.scale: 0.5
        checked: true
        contentItem: Text{
            anchors.fill: parent
            text: styleData.value
            color: "yellow"
        }

        onCheckStateChanged: {
            console.log("selected " + styleData.row + " status " + checked)
        }
    }
}
