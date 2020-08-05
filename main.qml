import QtQuick 2.15 as Quick
import QtQuick.Window 2.12
import TableModel 0.1 as Model
import QtQuick.Controls 1.4 as QuickCont

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
        }

        itemDelegate: Quick.TextInput {
            selectByMouse: true
            text: _tableView.model.rows[styleData.row][styleData.column].toString()
        }
    }
}
