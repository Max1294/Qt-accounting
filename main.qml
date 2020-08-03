import QtQuick 2.15
import QtQuick.Window 2.12
//import Qt.labs.qmlmodels 1.0
import TableModel 0.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4


ApplicationWindow {
    width: 400
    height: 400
    visible: true

    TableView {
        id: _tableView
        anchors.fill: parent
//        columnSpacing: 1
//        rowSpacing: 1
//        boundsBehavior: Flickable.StopAtBounds
//        columnWidth
        model: TableModel{}

        Component.onCompleted: {
            console.log(_tableView.columnCount)
        }

        headerDelegate: Rectangle {
            Repeater {
                model: _tableView.columnCount
                Text {text: "text"}
            }
        }
//        delegate: Rectangle{
//            implicitWidth: 50
//            implicitHeight: 50
//            Text{
//                text: "moc data"
//            }
//        }

//        itemDelegate: Text {
//            text: "text"
//        }




//        model: TableModel {
//            TableModelColumn { display: "checked" }
//            TableModelColumn { display: "amount" }
//            TableModelColumn { display: "fruitType" }
//            TableModelColumn { display: "fruitName" }
//            TableModelColumn { display: "fruitPrice" }

//            // Each row is one type of fruit that can be ordered
//            rows: [
//                {
//                    // Each property is one cell/column.
//                    checked: false,
//                    amount: 1,
//                    fruitType: "Apple",
//                    fruitName: "Granny Smith",
//                    fruitPrice: 1.50
//                },
//                {
//                    checked: true,
//                    amount: 4,
//                    fruitType: "Orange",
//                    fruitName: "Navel",
//                    fruitPrice: 2.50
//                },
//                {
//                    checked: false,
//                    amount: 1,
//                    fruitType: "Banana",
//                    fruitName: "Cavendish",
//                    fruitPrice: 3.50
//                }
//            ]
//        }
//        delegate:  TextInput {
//            text: model.display
//            padding: 12
//            selectByMouse: true

//            onAccepted: model.display = text

//            Rectangle {
//                anchors.fill: parent
//                color: "#efefef"
//                z: -1
//            }
//        }
    }
}
