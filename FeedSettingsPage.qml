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
                if (feedData.type === "REGEX") {
                    regexFeedType.checked = true;
                } else if (feedData.type === "XML_PATHEX") {
                    xmlPathexFeedType.checked = true;
                } else if (feedData.type === "JSON_PATHEX") {
                    jsonPathexFeedType.checked = true;
                }
                keyTextField.text = feedData.key;
                regexTextField.text = feedData.regex;
                keyRegexTextField.text = feedData.keyRegex;
                regexFieldsTextField.text = feedData.regexFields;
                xmlPathexTextField.text = feedData.xmlPathex;
                jsonPathexTextField.text = feedData.jsonPathex;
            }
        }
    }
    title: feedId ? "Update Feed" : "Create Feed"
    ScrollView {
        anchors.fill: parent
        Flickable {
            anchors.fill: parent
            contentHeight: stuff.implicitHeight
            ColumnLayout {
                id: stuff
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
                    }
                    Button {
                        text: "Paste"
                        onClicked: {
                            urlTextField.paste();
                        }
                    }
                }
                ColumnLayout {
                    ExclusiveGroup { id: feedTypeGroup }
                    RadioButton {
                        id: regexFeedType
                        text: "Regular Expression"
                        checked: true
                        exclusiveGroup: feedTypeGroup
                    }
                    RadioButton {
                        id: xmlPathexFeedType
                        text: "Path expression (XML)"
                        exclusiveGroup: feedTypeGroup
                    }
                    RadioButton {
                        id: jsonPathexFeedType
                        text: "Path expression (JSON)"
                        exclusiveGroup: feedTypeGroup
                    }
                }
                TextField {
                    id: keyTextField
                    Layout.fillWidth: true
                    placeholderText: "Key field name (optional)"
                }
                ColumnLayout {
                    visible: regexFeedType.checked
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
                        id: regexFieldsTextField
                        Layout.fillWidth: true
                        placeholderText: "Field names (comma-separated)"
                    }
                }
                ColumnLayout {
                    visible: xmlPathexFeedType.checked
                    TextField {
                        id: xmlPathexTextField
                        Layout.fillWidth: true
                        placeholderText: "XML path expression"
                    }
                }
                ColumnLayout {
                    visible: jsonPathexFeedType.checked
                    TextField {
                        id: jsonPathexTextField
                        Layout.fillWidth: true
                        placeholderText: "JSON path expression"
                    }
                }
                RowLayout {
                    Button {
                        id: submitButton
                        text: feedId ? "Update" : "Create"
                        onClicked: {
                            var feedType;
                            if (regexFeedType.checked) {
                                feedType = "REGEX";
                            } else if (xmlPathexFeedType.checked) {
                                feedType = "XML_PATHEX";
                            } else if (jsonPathexFeedType.checked) {
                                feedType = "JSON_PATHEX";
                            }
                            var feedData = {
                                name: nameTextField.text,
                                url: urlTextField.text,
                                type: feedType,
                                key: keyTextField.text,
                                regex: regexTextField.text,
                                keyRegex: keyRegexTextField.text,
                                regexFields: regexFieldsTextField.text,
                                xmlPathex: xmlPathexTextField.text,
                                jsonPathex: jsonPathexTextField.text
                            };
                            if (feedId) {
                                feedStore.save(feedId, feedData);
                            } else {
                                feedStore.save(feedData);
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