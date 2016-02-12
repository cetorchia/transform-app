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
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import Feeds 1.0
import Trees 1.0

Page {
    property var feedId
    FeedStore {
        id: feedStore
        onSaved: {
            // TODO: toast message nicely
            successMessageDialog.open();
        }
        onError: {
            // TODO: toast message nicely
            errorMessageDialog.text = message;
            errorMessageDialog.open();
        }
    }
    MessageDialog {
        id: successMessageDialog
        title: "Success"
        text: "Your feed has been saved."
        standardButtons: StandardButton.Ok
        onAccepted: {
            clearPages();
            goTo("MainPage.qml");
        }
    }
    MessageDialog {
        id: errorMessageDialog
        title: "Error"
        standardButtons: StandardButton.Ok
    }
    Component.onCompleted: {
        if (params.id) {
            var response = feedStore.get(params.id);
            if (Object.keys(response).length > 0) {
                feedId = response.id;
                var feedData = response.data;
                nameTextField.text = feedData.name;
                urlTextField.text = feedData.url;
                if (urlTextField.text) {
                    treeModel.loadFromUrl(urlTextField.text);
                }
                queryEditor.queryElementListModel.queryElements = feedData.query;
            }
        }
    }
    title: feedId ? "Edit Feed" : "Create Feed"
    ColumnLayout {
        anchors.fill: parent
        TextField {
            id: nameTextField
            Layout.fillWidth: true
            placeholderText: "Name"
        }
        RowLayout {
            TextField {
                id: urlTextField
                Layout.fillWidth: true
                placeholderText: "URL (optional)"
                onEditingFinished: {
                    if (urlTextField.text) {
                        treeModel.loadFromUrl(urlTextField.text);
                    }
                }
            }
            Button {
                text: "Paste"
                onClicked: {
                    urlTextField.paste();
                }
            }
        }
        TreeListView {
            id: treeListView
            visible: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: TreeModel {
                id: treeModel
                onError: {
                    // TODO: toast message nicely
                    errorMessageDialog.text = message;
                    errorMessageDialog.open();
                }
            }
            onSelectedElementChanged: {
                if (selectedElement.hasChildren === false) {
                    treeListView.visible = false;
                    queryEditor.open(treeListView.selectedElement);
                }
            }
        }
        QueryEditor {
            id: queryEditor
            Layout.fillWidth: true
            Layout.fillHeight: true
            onAccepted: {
                treeModel.goParent();
                treeListView.visible = true;
            }
            onRejected: {
                treeModel.goParent();
                treeListView.visible = true;
            }
        }
        Button {
            id: submitButton
            text: "Save"
            enabled: !queryEditor.visible
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            Layout.fillWidth: true
            onClicked: {
                var feedData = {
                    name: nameTextField.text,
                    url: urlTextField.text,
                    query: queryEditor.queryElementListModel.queryElements
                };
                if (feedId) {
                    feedStore.save(feedId, feedData);
                } else {
                    feedStore.save(feedData);
                }
            }
        }
    }
}
