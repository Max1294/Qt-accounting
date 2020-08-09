import QtQuick 2.15 as Quick
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import TableModel 1.0 as DBModel
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
        QuickCont.TableViewColumn{width: _tableView.width / _tableView.model.columnCount();}
    }

    QuickCont.TableView {
        id: _tableView
        anchors.fill: parent
        sortIndicatorVisible: true
        sortIndicatorOrder: Qt.DescendingOrder
        sortIndicatorColumn: 1

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

        model: DBModel.DatabaseModel{}

        itemDelegate: Quick.Rectangle{
            property var index: [-1, -1]
            property string text: ""

            id: _itemDelegate
            color: "black"
            width: _tableView.width / _tableView.model.columnCount()
            border.width: 1
            border.color: "green"
                Quick.TextEdit {
                    function foo(string) {
                        console.log("str " + string)
                        return string
                    }

                id: _edit
                color: "white"
                text: _tableView.model.rows[styleData.row][styleData.column].toString()
                font.pointSize: 8
                anchors.centerIn: _itemDelegate

                onContentSizeChanged: {
                    index = [styleData.row, styleData.column]
                    text = _edit.text
                }

                onActiveFocusChanged: {
                    foo(text)
                    _tableView.model.updateData(index[0], index[1], text)
                }

            }
        }

        headerDelegate: Quick.Rectangle{
            id: _headerDelegate
            border.width: 1
            border.color: "green"
            height: 100
            color: "grey"

            Quick.Text {
                text: styleData.value
                color: "lightblue"
                font.pointSize: 8
                anchors.centerIn: _headerDelegate
            } // Text
        }

        rowDelegate: Quick.Rectangle {
            id: _rowDeleg
            color: "lightsteelblue"
            height: 30
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
                        text: qsTr("edit row")
                    }
                    QuickCont.MenuItem {
                        text: qsTr("copy row")
                    }
                    QuickCont.MenuItem {
                        text: qsTr("replace row")
                    }
                    QuickCont.MenuItem {
                        text: qsTr("delete row")
                    }
                } // Menu
            } // MouseArea
        } // rowDelegate: Rectangle
    } // TableView
}
