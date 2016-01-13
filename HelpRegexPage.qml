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
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

Page {
    title: "Help: Regular Expressions"
    Layout.fillWidth: true
    ColumnLayout {
        anchors.fill: parent
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            TextArea {
                anchors.fill: parent
                readOnly: true
                text: "What are regular expressions?\n\n" +
                      "Regular expressions, or commonly just \"regex\" or \"regexp\", are simply " +
                      "patterns that determine how the program should match text from the data source.\n\n" +
                      "A very simple example is to match all dollar amounts like $501.97 in your text data. " +
                      "To do this, enter \$(\\d+\\.\\d+) into the Regular Expression field. " +
                      "The pattern is telling the program to first look for a dollar sign ($), " +
                      "then at least one digit (\\d+), and then a period (.), and finally at least one digit " +
                      "again. The resulting value will be captured as indicated between parentheses as (\\d+\\.\\d+) " +
                      "You need to specify the name of the field where this value is placed, so enter \"Price\" " +
                      "into Fields.\n\n" +
                      "To learn all about regular expressions, the button below links to a web page " +
                      "containing a tutorial."
            }
        }
        Button {
            text: "Regular Expression Tutorial"
            onClicked: {
                Qt.openUrlExternally("http://www.regular-expressions.info/tutorial.html");
            }
        }
    }
}
