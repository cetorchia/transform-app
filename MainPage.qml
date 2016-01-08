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
import QtQuick.Dialogs 1.2
import Feeds 1.0

Page {
    title: "Feeds"
    FeedStore {
        id: feedStore
        onError: {
            // TODO: toast message nicely
            errorMessageDialog.text = message;
            errorMessageDialog.open();
        }
    }
    MessageDialog {
        id: errorMessageDialog
        title: "Error"
        standardButtons: StandardButton.Ok
    }
    ListModel {
        id: feedListModel
        Component.onCompleted: {
            var feeds = feedStore.get();
            feeds.forEach(function(feedData) {
                var feedType;
                if (feedData.data.type == "REGEX") {
                    feedType = "Regular expression";
                } else if (feedData.data.type == "XML_PATHEX") {
                    feedType = "Path expression (XML)";
                } else if (feedData.data.type == "JSON_PATHEX") {
                    feedType = "Path expression (JSON)";
                }
                var element = {
                    feedId: feedData.id,
                    name: feedData.data.name,
                    feedType: feedType
                };
                feedListModel.append(element);
            });
        }
    }
    ColumnLayout {
        anchors.fill: parent
        Button {
            id: createFeedButton
            text: "Create Feed"
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.fillWidth: true
            onClicked: goTo("CreateFeedPage.qml");
        }
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ListView {
                anchors.fill: parent
                model: feedListModel
                focus: true
                spacing: 2
                delegate: ListViewItem {
                    RowLayout {
                        anchors.fill: parent
                        ColumnLayout {
                            Layout.fillHeight: true
                            Layout.fillWidth: false
                            Label {
                                Layout.leftMargin: 10
                                text: name
                                font.bold: true
                            }
                            Label {
                                Layout.leftMargin: 10
                                text: feedType
                                font.italic: true
                            }
                        }
                        Item { Layout.fillWidth: true }
                        ListViewItemButton {
                            Layout.fillWidth: false
                            onClicked: function() {
                                goTo("CreateFeedPage.qml", {id: feedId});
                            }
                            Image {
                                anchors.fill: parent
                                source: "qrc:/settings49.png"
                                sourceSize.width: 32
                                sourceSize.height: 32
                            }
                        }
                    }
                    onClicked: function() {
                         // TODO: Go to view feed page where they can view details
                         // of the feed, as well as view its output.
                         goTo("CreateFeedPage.qml", {id: feedId});
                    }
                }
            }
        }
    }
}
