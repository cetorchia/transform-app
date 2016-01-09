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
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import Feeds 1.0

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
                    text: feedData.name
                    font.bold: true
                }
                Label {
                    property string value: feedData.type
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
                        text: feedData.url
                        font.family: "monospace"
                    }
                }
                RowLayout {
                    Label {
                        text: "Key field name:"
                        font.bold: true
                    }
                    Label {
                        text: feedData.key
                        font.family: "monospace"
                    }
                }
                ColumnLayout {
                    visible: (feedData.type === "REGEX")
                    RowLayout {
                        Label {
                            text: "Regular expression:"
                            font.bold: true
                        }
                        Label {
                            text: feedData.regex
                            font.family: "monospace"
                        }
                    }
                    RowLayout {
                        Label {
                            text: "Key regular expression:"
                            font.bold: true
                        }
                        Label {
                            text: feedData.keyRegex
                            font.family: "monospace"
                        }
                    }
                    RowLayout {
                        Label {
                            text: "Field names:"
                            font.bold: true
                        }
                        Label {
                            text: feedData.regexFields
                            font.family: "monospace"
                        }
                    }
                }
                ColumnLayout {
                    visible: (feedData.type === "XML_PATHEX")
                    RowLayout {
                        Label {
                            text: "XML path expression:"
                            font.bold: true
                        }
                        Label {
                            text: feedData.xmlPathex
                            font.family: "monospace"
                        }
                    }
                }
                ColumnLayout {
                    visible: (feedData.type === "JSON_PATHEX")
                    RowLayout {
                        Label {
                            text: "JSON path expression:"
                            font.bold: true
                        }
                        Label {
                            text: feedData.jsonPathex
                            font.family: "monospace"
                        }
                    }
                }
                Label {
                    text: "Data"
                    font.bold: true
                }
                ColumnLayout {
                    visible: (!feedData.url)
                    Layout.fillWidth: true
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
                Item {
                    id: keepMeAtTheBottomToPreserveAlignment
                    Layout.fillHeight: true
                }
            }
        }
    }
}
