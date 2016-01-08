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
    property var feedId: params.id
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
    }
    Component.onCompleted: {
        if (feedId) {
            var response = feedStore.get(feedId);
            if (Object.keys(response).length > 0) {
                var feedData = response.data;
                nameLabel.text = feedData.name;
                urlLabel.text = feedData.url;
                typeLabel.value = feedData.type;
                keyLabel.text = feedData.key;
                regexLabel.text = feedData.regex;
                keyRegexLabel.text = feedData.keyRegex;
                regexFieldsLabel.text = feedData.regexFields;
                xmlPathexLabel.text = feedData.xmlPathex;
                jsonPathexLabel.text = feedData.jsonPathex;
            }
        }
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
                    id: nameLabel
                    font.bold: true
                }
                Label {
                    id: typeLabel
                    property string value
                    text: if (value === "REGEX") {
                              "Regular expression"
                          } else if (value === "XML_PATHEX") {
                              "Path expression (XML)"
                          } else if (value === "JSON_PATHEX") {
                              "Path expression (JSON)"
                          }
                    font.italic: true
                }
                RowLayout {
                    Label {
                        text: "URL:"
                        font.bold: true
                    }
                    Label {
                        id: urlLabel
                        font.family: "monospace"
                    }
                }
                RowLayout {
                    Label {
                        text: "Key field name:"
                        font.bold: true
                    }
                    Label {
                        id: keyLabel
                        font.family: "monospace"
                    }
                }
                ColumnLayout {
                    visible: typeLabel.value === "REGEX"
                    RowLayout {
                        Label {
                            text: "Regular expression:"
                            font.bold: true
                        }
                        Label {
                            id: regexLabel
                            font.family: "monospace"
                        }
                    }
                    RowLayout {
                        Label {
                            text: "Key regular expression:"
                            font.bold: true
                        }
                        Label {
                            id: keyRegexLabel
                            font.family: "monospace"
                        }
                    }
                    RowLayout {
                        Label {
                            text: "Field names:"
                            font.bold: true
                        }
                        Label {
                            id: regexFieldsLabel
                            font.family: "monospace"
                        }
                    }
                }
                ColumnLayout {
                    visible: (typeLabel.value === "XML_PATHEX")
                    RowLayout {
                        Label {
                            text: "XML path expression:"
                            font.bold: true
                        }
                        Label {
                            id: xmlPathexLabel
                            font.family: "monospace"
                        }
                    }
                }
                ColumnLayout {
                    visible: (typeLabel.value === "JSON_PATHEX")
                    RowLayout {
                        Label {
                            text: "JSON path expression:"
                            font.bold: true
                        }
                        Label {
                            id: jsonPathexLabel
                            font.family: "monospace"
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
