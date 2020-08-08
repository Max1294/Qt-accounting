import QtQuick 2.15 as Quick
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import TableModel 0.1 as Model
import QtQuick.Controls 1.4 as QuickCont
import QtQuick.Controls.Styles 1.4
import QtQml 2.15

QuickCont.ApplicationWindow {
    width: 400
    height: 400
    visible: true

    Quick.Component
    {
        id: columnComponent
        QuickCont.TableViewColumn{width: _tableView.width / _tableView.model.columnCount()} // set width
    }

    QuickCont.TableView {
        id: _tableView
        anchors.fill: parent
//        backgroundVisible: false
//        sortIndicatorVisible: true
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

        model: Model.TableModel{}

        itemDelegate: Quick.Rectangle{
            id: _itemDelegate
            color: "black"
            width: _tableView.width / _tableView.model.columnCount()
            border.width: 1
            border.color: "green"
                Quick.Text {
                color: "white"
                text: _tableView.model.rows[styleData.row][styleData.column].toString()
                font.pointSize: 8
                anchors.centerIn: _itemDelegate
            }
        }


        headerDelegate: Quick.Rectangle{
            id: _headerDelegate
            border.width: 1
            border.color: "green"
            height: 50
            color: "grey"
            Quick.Text {
            text: styleData.value
            color: "lightblue"
            font.pointSize: 8
            anchors.centerIn: _headerDelegate

            Connections{
                target: styleData
//                on: console.log("sdf")
                onPressedChanged: _tableView.model.moveColumn(0, 1)//styleData.value !== _tableView.model.roles[styleData.column] ?
                                      //console.log("column " + styleData.column) : _tableView.model.setQuery("SELECT * FROM Contacts WHERE " + _tableView.model.roles[styleData.column] +"='Eric'")
            }
        }
        }

        rowDelegate: Quick.Rectangle {
            id: _rowDeleg
            color: "lightsteelblue"
            height: 20
            border.width: 1
            Quick.MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                hoverEnabled: true

                // TODO: click -> open options: edir, delete, copy, paste
                onClicked: {
                    if(mouse.button === Qt.RightButton)
                        _flipMenu.popup()
                }

                onEntered: {
                    if(entered) {
                        _rowDeleg.color = "green"
                    }


                    console.log(styleData.row)
                }

                onExited: {
                    if(exited)
                        _rowDeleg.color = "lightsteelblue"
                }

                QuickCont.Menu {
                    id: _flipMenu
                    QuickCont.MenuItem {
                        text: qsTr("edit")
//                        Component.completed: {
//                            console.log(styleData.row + " " + styleData.row)
//                        }

                    }
                    QuickCont.MenuItem {
                        text: qsTr("copy")
                    }
                    QuickCont.MenuItem {
                        text: qsTr("paste")
                    }
                    QuickCont.MenuItem {
                        text: qsTr("delete")
                    }
                } // Menu
            } // MouseArea
        } // rowDelegate: Rectangle
    }
}
