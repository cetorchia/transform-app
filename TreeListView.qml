/* This file is part of the transform app
 * Copyright (c) 2016 Carlos E. Torchia
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
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import Trees 1.0

Item {
    id: treeListView
    property var selectedElement: model.currentItemData
    property TreeModel model: TreeModel {
    }
    ColumnLayout {
        anchors.fill: parent
        Label {
            id: label
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: "Select elements from the following data to query."
        }
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ListView {
                id: listView
                model: treeListView.model.currentList
                spacing: 2
                delegate: ListViewItem {
                    RowLayout {
                        anchors.fill: parent
                        ColumnLayout {
                            Layout.fillHeight: true
                            Layout.fillWidth: false
                            Label {
                                Layout.leftMargin: 10
                                text: modelData.name
                                font.bold: true
                            }
                        }
                    }
                    onClicked: if (modelData.isParent) {
                                   treeListView.model.goParent()
                               } else {
                                   treeListView.model.go(modelData.row);
                               }
                }
            }
        }
    }
}
