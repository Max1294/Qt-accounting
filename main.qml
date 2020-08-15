import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15
import MainWindowComponents 1.0

import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    id: _root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TabView
    {
        function add() {
            var tab = _tabView.addTab("title", columnComponent)
            console.log("index " + currentIndex)
        }

        id: _tabView
        anchors.fill: parent

        style: TabViewStyle{
            tabsMovable: true
        }

                            Tab {
                                id: _tab1
                                width: _tabView.width
                                height: _tabView.height
                                title: "tab_1"

                                DBArea {
                                    anchors.fill: _tab1
                                } // DBArea

                            } // Tab


        Component
            {
                id: columnComponent
                Tab {
//                    width: _tabView.width
//                    height: _tabView.height
                    title: "tab_1"
                                            DBArea {
                                                width: 300
                                                height: 300
                                            } // DBArea
                } // Tab
            }

        Component.onCompleted: {
            add()
            add()
        }
    }


//    MainArea {
//        anchors.top: _menuBar.bottom
//        anchors.fill: parent
//    }

//    menuBar: MenuBarArea {
//        id: _menuBar
//        width: _root.width
//        height: Math.min(40, _root.height)
//    }
}
