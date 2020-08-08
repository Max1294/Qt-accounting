import QtQuick 2.15 as Quick
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import TableModel 0.1 as Model
import QtQuick.Controls 1.4 as QuickCont
import QtQuick.Controls.Styles 1.4

QuickCont.ApplicationWindow {
    width: 400
    height: 400
    visible: true

    Quick.Component
    {
        id: columnComponent
        QuickCont.TableViewColumn{width: 200} // set width
    }

    QuickCont.TableView {
        id: _tableView
        anchors.fill: parent
//        backgroundVisible: false
        sortIndicatorVisible: true

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

        headerDelegate: Quick.Text {
            text: styleData.value
            color: "yellow"
            Quick.MouseArea {
                anchors.fill: parent

                hoverEnabled: true

                onEntered: {
                    if(entered){
                        console.log("done")
                    }
                }
            }
        }

        itemDelegate: Quick.Text {
//            selectByMouse: true
//            overwriteMode: true
//            selectionColor: "red"
//            activeFocusOnPress: false
            color: "#9932CC"
            text: _tableView.model.rows[styleData.row][styleData.column].toString()
        }

        // TODO
        style: TableViewStyle {
//            itemDelegate: Quick.Rectangle{
//                id: _itemDelegate
//                Quick.MouseArea {
//                    anchors.fill: parent
//                    acceptedButtons: Qt.LeftButton
//                    hoverEnabled: true

//                    onDoubleClicked: {
//                        if(doubleClicked)
//                        {
//                            console.log("double clicked")
//                        }
//                    }
//                }
//            }

            rowDelegate: Quick.Rectangle {
                id: _rowDeleg
                color: "lightsteelblue"
                height: 20
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
                        if(entered)
                            _rowDeleg.color = "green"
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
//                            Action{}
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
}
