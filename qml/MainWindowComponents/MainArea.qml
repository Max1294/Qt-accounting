import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

SplitView {
    Item {
        id: _parentItem
        width: parent.width / 3
        Layout.minimumWidth: Math.min(100, _root.width * 0.3)
        Layout.maximumWidth: _root.width * 0.7

        DBInfoArea {
            anchors.fill: parent
        } // DBInfoArea
    } // Item

    Item {
        id: _mainArea
         width: parent.width / 2
         Layout.maximumWidth: _root.width * 0.9
         Column {
            Repeater {
                model: 1
                TabView
                {
                    id: _tabView
                    width: _root.width - _parentItem.width
                    height: _root.height - _menuBar.height

                    Tab {
                        id: _tab1
                        width: _tabView.width
                        height: _tabView.height
                        title: "tab_1"

                        DBArea {
                            anchors.fill: _tab1
                        } // DBArea

                    } // Tab

                    Tab {
                        id: _tab2
                        title: "tab_2"

                        Rectangle {
                            width: _tab2.width
                            height: _tab2.height
                            color: "green"
                        } // Rectangle
                    } // Tab
                } // TabView
            } // Repeater
         } // Column
    } // Item
} // SplitView
