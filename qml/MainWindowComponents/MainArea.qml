import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick 2.15

TabView
{
    id: _tabView

    Component{
        id: _tab

        DBArea {
            id: _tArea
            anchors.fill: parent
        }
    } // Component

    Component.onCompleted: {
        _tabView.addTab("Contacts", _tab)
        _tabView.addTab("AddressBook", _tab)
    }

    onCurrentIndexChanged: {
        console.log("index " + currentIndex)
    }
} // TabView
