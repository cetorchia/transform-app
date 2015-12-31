/* This file is part of the transform app
 * Copyright (c) 2015 Carlos E. Torchia
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

import "about.js" as About

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: About.workName + " (c) " + About.copyright + " (see License for terms and conditions)"
    StackView {
        id: stackView
        anchors.fill: parent
        // Implements back key navigation
        focus: true
        Keys.onReleased: if (event.key === Qt.Key_Back && stackView.depth > 1) {
                             stackView.pop();
                             event.accepted = true;
                         }
        initialItem: MainPage {
        }
    }
    function goTo(qmlFile) {
        if (stackView.currentItem.goTo) {
            stackView.currentItem.goTo(qmlFile)
        }
    }
    toolBar: ToolBar {
        RowLayout {
            Layout.maximumHeight: 32
            anchors.fill: parent
            ToolButton {
                Layout.fillWidth: false
                onClicked: stackView.pop();
                Image {
                    anchors.fill: parent
                    source: "qrc:/back57.png"
                    sourceSize.width: 32
                    sourceSize.height: 32
                }
            }
            Item {
                Layout.fillWidth: true
            }
            Label {
                id: titleLabel
                text: stackView.currentItem.title ? stackView.currentItem.title : ""
            }
            Item {
                Layout.fillWidth: true
            }
            ToolButton {
                Layout.alignment: Qt.AlignRight
                menu: Menu {
                    title: qsTr("Menu")
                    MenuItem {
                        text: qsTr("About")
                        onTriggered: goTo("AboutPage.qml");
                    }
                    MenuItem {
                        text: qsTr("License")
                        onTriggered: goTo("LicensePage.qml");
                    }
                    MenuItem {
                        text: qsTr("Source Code")
                        onTriggered: Qt.openUrlExternally(About.sourceCodeUrl);
                    }
                    MenuItem {
                        text: qsTr("Exit")
                        onTriggered: Qt.quit();
                    }
                }
            }
        }
    }
}
