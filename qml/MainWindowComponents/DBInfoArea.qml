import QtQuick 2.0
import QtQuick.Controls 1.4
import TreeViewModel 1.0

TreeView {
    backgroundVisible: false

    headerVisible: false

    TableViewColumn{
        width: 100
        role: "display"
        title: "Elements"
    }


//    itemDelegate: _listDelegate

    itemDelegate: CheckBox {
        id: checkBox

        text: qsTr("text", "black")
    }

//    Component {
//        id: _listDelegate
//        Item {
//            id: _delegate

//            CheckBox {
//                id: checkBox

//                text: qsTr("text", "black")
//            }
//        }
//    }


    model: TreeViewModel{}
}
