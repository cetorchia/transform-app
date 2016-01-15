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
import Transformation 1.0
import Export 1.0

import "util.js" as Util

Page {
    property var feedId
    property var feedData: ({})
    title: "Feed"
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
        onAccepted: {
            closePage();
        }
    }
    Component.onCompleted: {
        if (params.id) {
            var response = feedStore.get(params.id);
            if (Object.keys(response).length > 0) {
                feedId = response.id;
                feedData = response.data;
                if (feedData.url) {
                    doTransform();
                }
            }
        }
    }
    function doTransform() {
        if (!feedData.url) {
            dataTransformer.transform(feedData, dataTextArea.text);
        } else {
            dataTransformer.transform(feedData);
        }
    }
    DataTransformer {
        id: dataTransformer
        onError: {
            // TODO: toast message nicely
            errorMessageDialog.text = message;
            errorMessageDialog.open();
        }
        onFinished: {
            var transformedData = outData;
            var fields = outFields;
            if (transformedData.length > 0) {
                for (var i = tableView.columnCount - 1; i >= 0; i--) {
                    tableView.removeColumn(i);
                }
                fields.forEach(function(field) {
                    var tableViewColumn = tableViewColumnComponent.createObject(tableView, {
                                                                                    role: field,
                                                                                    title: field
                                                                                });
                    tableView.addColumn(tableViewColumn);
                });
                transformedDataListModel.clear();
                transformedData.forEach(function(object) {
                    var escapedObject = Util.escapeObject(object);
                    transformedDataListModel.append(escapedObject);
                });
                csvExporter.fields = fields;
                csvExporter.data = transformedData;
            } else {
                noResultsMessageDialog.open();
            }
        }
    }
    ListModel {
        id: transformedDataListModel
    }
    MessageDialog {
        id: noResultsMessageDialog
        title: "No results"
        standardButtons: StandardButton.Ok
        text: "Feed pattern(s) do not match any part of the data."
    }
    CsvExporter {
        id: csvExporter
        filename: feedData.name + ".csv"
        onFinished: {
            csvExportMessageDialog.text = "Data written to " + path
            csvExportMessageDialog.open();
        }
        onError: {
            csvExportMessageDialog.text = message
            csvExportMessageDialog.open();
        }
    }
    MessageDialog {
        id: csvExportMessageDialog
        title: "CSV Export"
        standardButtons: StandardButton.Ok
    }
    ScrollView {
        anchors.fill: parent
        Flickable {
            anchors.fill: parent
            contentHeight: stuff.implicitHeight
            ColumnLayout {
                id: stuff
                anchors.fill: parent
                Label {
                    text: feedData.name
                    font.bold: true
                }
                RowLayout {
                    Label {
                        text: "URL:"
                        font.bold: true
                    }
                    Label {
                        text: feedData.url
                        font.family: "monospace"
                    }
                }
                Label {
                    text: "Data"
                    font.bold: true
                }
                ColumnLayout {
                    visible: (feedId && !feedData.url)
                    Layout.fillWidth: true
                    Button {
                        text: "Paste from clipboard"
                        onClicked: {
                            dataTextArea.paste();
                        }
                    }
                    Label {
                        text: "Input data to transform:"
                        font.italic: true
                    }
                    TextArea {
                        id: dataTextArea
                        Layout.fillWidth: true
                        width: parent.width
                        height: 300
                    }
                }
                RowLayout {
                    visible: (feedId && !feedData.url) || (transformedDataListModel.count > 0)
                    Layout.fillWidth: true
                    Button {
                        text: (transformedDataListModel.count === 0) ? "Go" : "Reload"
                        onClicked: {
                            doTransform();
                        }
                    }
                    Item { Layout.fillWidth: true }
                    Button {
                        visible: csvExporter.data.length > 0 ? true : false
                        text: "Export as CSV"
                        onClicked: {
                            csvExporter.save();
                        }
                    }
                    Button {
                        visible: csvExporter.data.length > 0 ? true : false
                        text: "Copy to clipboard"
                        onClicked: {
                            csvExporter.copy();
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                    height: 450
                    TableView {
                        id: tableView
                        visible: (transformedDataListModel.count > 0)
                        model: transformedDataListModel
                        anchors.fill: parent
                        Component {
                            id: tableViewColumnComponent
                            TableViewColumn {
                            }
                        }
                    }
                }
                Item {
                    id: keepMeAtTheBottomToPreserveAlignment
                    Layout.fillHeight: true
                }
            }
        }
    }
}
