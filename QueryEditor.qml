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
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import Feeds 1.0

import "theme.js" as Theme

Item {
    id: queryEditor
    signal accepted
    signal rejected
    property QueryElementListModel queryElementListModel: QueryElementListModel {
    }
    visible: false
    function open(selectedElement) {
        var queryElement = queryElementListModel.get(selectedElement.pathex, selectedElement.name);
        pathexTextField.text = queryElement.pathex;
        fieldsTextField.text = queryElement.fields;
        regexTextField.text = queryElement.regex;
        keyTextField.text = queryElement.key;
        keyRegexTextField.text = queryElement.keyRegex;
        queryEditor.visible = true;
    }
    function save() {
        queryElementListModel.put(
                    pathexTextField.text,
                    fieldsTextField.text,
                    regexTextField.text,
                    keyTextField.text,
                    keyRegexTextField.text
                    );
    }
    Rectangle {
        anchors.fill: parent
        color: Theme.widgetBackground
        border.color: Theme.widgetBorder
        radius: 3
    }
    ScrollView {
        anchors.fill: parent
        ColumnLayout {
            width: queryEditor.width
            ColumnLayout {
                id: stuff
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignTop
                Label {
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                    text: "To query this element, make any necessary modifications and press OK."
                }
                TextField {
                    id: pathexTextField
                    Layout.fillWidth: true
                    placeholderText: "Path expression"
                    readOnly: true
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
                        placeholderText: "Regular expression (optional)"
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
                RowLayout {
                    Button {
                        text: "Cancel"
                        onClicked: {
                            queryEditor.visible = false;
                            queryEditor.rejected();
                        }
                    }
                    Button {
                        text: "OK"
                        onClicked: {
                            queryEditor.save();
                            queryEditor.visible = false;
                            queryEditor.accepted();
                        }
                    }
                }
            }
        }
    }
}
