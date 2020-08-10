import QtQuick 2.15 as Quick
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import TableModel 1.0 as DBModel
import QtQuick.Controls 1.4 as QuickCont
import QtQuick.Controls.Styles 1.4

QuickCont.TableView {
    id: _tableView
    anchors.fill: _tab1
    sortIndicatorVisible: true
    sortIndicatorOrder: Qt.DescendingOrder
    sortIndicatorColumn: 1

    Quick.Component
    {
        id: columnComponent
        QuickCont.TableViewColumn{width: _tableView.width / _tableView.model.columnCount();}
    }

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

              onEditingFinished: {
                index = [styleData.row, styleData.column]
                if(_tableView.model.rows[index[0]][index[1]] !== _edit.text)
                {
                    console.log("Update " + index)
                     _tableView.model.updateData(index[0], index[1], text)
                }

                console.log("YE$S " + index + " model text " + _tableView.model.rows[index[0]][index[1]]
                            + " text " + _edit.text)
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
                if(mouse.button === Qt.RightButton){
                    _flipMenu.popup()
                    console.log(styleData.row)
                }
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
