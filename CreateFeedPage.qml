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

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import Feeds 1.0

Page {
    Feed {
        id: feed
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
    title: "Create Feed"
    RegExpValidator {
        id: requiredValidator
        regExp: /^.+$/
    }
    ColumnLayout {
        anchors.fill: parent
        TextField {
            id: nameTextField
            Layout.fillWidth: true
            placeholderText: "Name"
            validator: requiredValidator
        }
        TextField {
            id: urlTextField
            Layout.fillWidth: true
            placeholderText: "URL (optional)"
        }
        RowLayout {
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
            TextField {
                id: regexTextField
                Layout.fillWidth: true
                placeholderText: "Regular expression"
            }
            TextField {
                id: keyRegexTextField
                Layout.fillWidth: true
                placeholderText: "Key regular expression (optional)"
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
                text: "Create"
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
                    console.log(JSON.stringify(feedData));
                    feed.save(JSON.stringify(feedData));
                }
            }
        }
        Item {
            id: keepMeAtTheBottomToPreserveAlignment
            Layout.fillHeight: true
        }
    }
}
