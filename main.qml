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

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import "about.js" as About

ApplicationWindow {
    visible: true
    width: 480
    height: 640
    title: About.workName + " (c) " + About.copyright + " (see License for terms and conditions)"
    PageView {
        id: pageView
        initialItem: MainPage {
        }
    }
    toolBar: ToolBar {
        RowLayout {
            Layout.maximumHeight: 32
            anchors.fill: parent
            ToolButton {
                Layout.fillWidth: false
                onClicked: pageView.pop();
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
                text: pageView.title
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
                        onTriggered: pageView.goTo("AboutPage.qml");
                    }
                    MenuItem {
                        text: qsTr("License")
                        onTriggered: pageView.goTo("LicensePage.qml");
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
