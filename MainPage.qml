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
        onDeleted: {
            getFeeds();
        }
    }
    MessageDialog {
        id: errorMessageDialog
        title: "Error"
        standardButtons: StandardButton.Ok
    }
    function getFeeds() {
        var feeds = feedStore.get();
        feedListModel.clear();
        feeds.forEach(function(feedData) {
            var element = {
                feedId: feedData.id,
                feedName: feedData.data.name,
            };
            feedListModel.append(element);
        });
    }
    Component.onCompleted: {
        getFeeds();
    }
    ListModel {
        id: feedListModel
    }
    function deleteFeed(feedId, feedName) {
        areYouSureMessageDialog.feedId = feedId;
        areYouSureMessageDialog.feedName = feedName;
        areYouSureMessageDialog.open();
    }
    MessageDialog {
        id: areYouSureMessageDialog
        property int feedId
        property string feedName
        title: "Are you sure?"
        text: "This feed " + feedName + " would be deleted."
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            feedStore.remove(feedId);
        }
    }
    ColumnLayout {
        anchors.fill: parent
        Button {
            id: createFeedButton
            text: "Create Feed"
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.fillWidth: true
            onClicked: goTo("FeedSettingsPage.qml");
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
                                text: feedName
                                font.bold: true
                            }
                        }
                        Item { Layout.fillWidth: true }
                        ListViewItemButton {
                            Layout.fillWidth: false
                            onClicked: function() {
                                goTo("FeedSettingsPage.qml", {id: feedId});
                            }
                            Image {
                                anchors.fill: parent
                                source: "qrc:/settings49.png"
                                sourceSize.width: 32
                                sourceSize.height: 32
                            }
                        }
                        ListViewItemButton {
                            Layout.fillWidth: false
                            onClicked: function() {
                                deleteFeed(feedId, feedName)
                            }
                            Image {
                                anchors.fill: parent
                                source: "qrc:/close47.png"
                                sourceSize.width: 32
                                sourceSize.height: 32
                            }
                        }
                    }
                    onClicked: function() {
                         goTo("FeedPage.qml", {id: feedId});
                    }
                }
            }
        }
    }
}
