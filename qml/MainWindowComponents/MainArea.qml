import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

TabView
{
    id: _tabView

    Component.onCompleted: {
        loadTab()
        loadTab()
        loadTab()
    }

    Component{
        id: _tab
        Column{
        GridView {
            width: _tabView.width
            height: 30
            cellHeight: 30
            cellWidth: 200
            model: 3

            delegate: Rectangle{
                id: _delegate
//                width: 200
//                height: 30
                color: "green"
                TextArea{
                    anchors.centerIn: _delegate
                    placeholderText: "Filter"
                }
            }
        }
        DBArea{
            width: _tabView.width
            height: _tabView.height - 30
//            anchors.fill:parent
        }
        }
    }

    function loadTab(){
        _tabView.addTab("title", _tab)
    }
} // TabView
