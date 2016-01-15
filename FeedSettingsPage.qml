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
                pathexTextField.text = feedData.query[0].pathex;
                fieldsTextField.text = feedData.query[0].fields.join(", ");
                regexTextField.text = feedData.query[0].regex;
                keyTextField.text = feedData.query[0].key;
                keyRegexTextField.text = feedData.query[0].keyRegex;
            }
        }
    }
    title: feedId ? "Update Feed" : "Create Feed"
    ScrollView {
        anchors.fill: parent
        Flickable {
            anchors.fill: parent
            ColumnLayout {
                width: parent.width
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
                                var request = new XMLHttpRequest();
                                request.open('GET', urlTextField.text);
                                request.onreadystatechange = function(event) {
                                    if (request.readyState === XMLHttpRequest.DONE) {
                                        var data = request.responseText;
                                        // TODO: parse data and set tree view
                                    }
                                }
                                //request.send();
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
                ColumnLayout {
                    TextField {
                        id: pathexTextField
                        Layout.fillWidth: true
                        placeholderText: "Path expression"
                    }
                    TextField {
                        id: fieldsTextField
                        Layout.fillWidth: true
                        placeholderText: "Field names (comma-separated)"
                    }
                    RowLayout {
                        TextField {
                            id: regexTextField
                            Layout.fillWidth: true
                            placeholderText: "Regular expression"
                        }
                        HelpButton {
                            onClicked: {
                                goTo("HelpRegexPage.qml");
                            }
                        }
                    }
                    TextField {
                        id: keyTextField
                        Layout.fillWidth: true
                        placeholderText: "Key field name (optional)"
                    }
                    RowLayout {
                        TextField {
                            id: keyRegexTextField
                            Layout.fillWidth: true
                            placeholderText: "Key regular expression (optional)"
                        }
                        HelpButton {
                            onClicked: {
                                goTo("HelpRegexPage.qml");
                            }
                        }
                    }
                }
                RowLayout {
                    Button {
                        id: submitButton
                        text: feedId ? "Update" : "Create"
                        onClicked: {
                            var fields;
                            if (fieldsTextField.text) {
                                fields = fieldsTextField.text.split(/\s*,\s*/);
                            } else {
                                fields = [];
                            }

                            var feedData = {
                                name: nameTextField.text,
                                url: urlTextField.text,
                                query: [
                                    {
                                        pathex: pathexTextField.text,
                                        fields: fields,
                                        regex: regexTextField.text,
                                        key: keyTextField.text,
                                        keyRegex: keyRegexTextField.text
                                    }
                                ]
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
        }
    }
}
