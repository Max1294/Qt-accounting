import QtQuick 2.15 as Quick
import QtQuick.Window 2.12
import TableModel 0.1 as Model
import QtQuick.Controls 1.4 as QuickCont

QuickCont.ApplicationWindow {
    width: 400
    height: 400
    visible: true



    property string roleName: _tableView.model.roles[1].toString()
//    property int currentIndex: -1
    Quick.Component
    {
        id: columnComponent
        QuickCont.TableViewColumn{width: 200} // set width
    }

    QuickCont.TableView {
        id: _tableView
        anchors.fill: parent
//        columnSpacing: 1
//        rowSpacing: 1
//        boundsBehavior: Flickable.StopAtBounds

        QuickCont.TableViewColumn{}

    resources: {
        var roleList = _tableView.model.roles
        var temp = []

        for(var i=0; i<roleList.length; i++)
        {
                var role  = roleList[i]
                temp.push(columnComponent.createObject(_tableView, {"title": role, "title": _tableView.model.roles[i]}))
        }
        return temp
    }


//    Quick.Component.onCompleted: {
//        console.log(_tableView.model.roles[0])
//    }

        model: Model.TableModel{}

//        delegate: Quick.Rectangle{
//            implicitWidth: 50
//            implicitHeight: 50
//            color: "green"
//            Quick.Text {
//                text: _tableView.model.roles
//            }
//        }

//        Quick.Component
//        {
//            id: rowComponent
////            Quick.Row{height: 100
////                width: 200
////                Quick.Text{text: "test"
////                color: "white"}
//            Quick.Rectangle{
//            width: 60
//            height: 100
//            color: "green"}
//        }
////        }

//        rowDelegate: Quick.Rectangle { // FIX
////            spacing: 10
//            resources: {
//                var rowList = _tableView.model.rows
//                var temp = []

//                for(var i=0; i<2; i++)
//                {
//                       temp.push(rowComponent.createObject(_tableView, {}))
//                }
//                return temp

//            }
////            Quick.Text {
////                text: _tableView.model.rows
////            }
//        }

        headerDelegate: Quick.Text {
                text: styleData.value
                color: "yellow"
//                anchors.centerIn: parent
            }


        Quick.Component.onCompleted: {
             console.log(_tableView.currentRow)
        }

//        delegate: Rectangle{
//            implicitWidth: 50
//            implicitHeight: 50
//            Text{
//                text: "moc data"
//            }
//        }

//        itemDelegate: Quick.TextInput {
//            selectByMouse: true
//            text: _tableView.model.rows[1].toString()
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
