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
        DBArea{
            anchors.fill:parent
        }
    }

    function loadTab(){
        _tabView.addTab("title", _tab)
    }
} // TabView
