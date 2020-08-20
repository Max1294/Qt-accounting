import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

TabView
{
    id: _tabView
    Component{
        id: _tab
        DBArea{
            id: _tArea
            width: _tabView.width
            height: _tabView.height - 30
        }
    } // Component

    Component.onCompleted: {
        _tabView.addTab("Contacts", _tab)
        _tabView.addTab("AddressBook", _tab)
//        for(var i = 0; i < 2; ++i)
//        {
//            _tabView.addTab("title", _tab)
//        }
    }

    onCurrentIndexChanged: {
        console.log("index " + currentIndex)
    }
} // TabView
