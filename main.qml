import QtQuick 2.15 as Quick
import QtQuick.Window 2.12
import TableModel 0.1 as Model
import QtQuick.Controls 1.4 as QuickCont


ApplicationWindow {
    width: 400
    height: 400
    visible: true

    Quick.TableView {
        id: _tableView
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
//        boundsBehavior: Flickable.StopAtBounds
//        Quick.Repeater{
//            model: 3
//            TableViewColumn {
//                role: "title"
//                title: "Title"
//                width: 100
//            }
//        }

        model: Model.TableModel{}

        delegate: Quick.Rectangle{
            implicitWidth: 50
            implicitHeight: 50
            color: "green"
            Quick.Text {
                text: _tableView.model.roles
            }
        }

        //        Component.onCompleted: {
        //            console.log(columnCount)
        //        }

//        rowDelegate: Rectangle {
//            Text {
//                text: "fdsahjks"
//            }
//        }
//        headerDelegate: Rectangle {
//            Repeater {
//                model: model.columnCount()
//                Text {text: "text"}
//            }
//        }
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
