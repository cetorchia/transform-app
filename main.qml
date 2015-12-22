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
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World!")

    menuBar: MenuBar {
        Menu {
            title: qsTr("Menu")
            MenuItem {
                text: qsTr("About")
                onTriggered: aboutDialog.open();
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    MessageDialog {
        id: aboutDialog
        title: "About"
        modality: Qt.WindowModal
        text: "Transform is an app that puts data analytics and visualization in your hands, on your mobile device."
        standardButtons: StandardButton.Ok
    }

    Label {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}

