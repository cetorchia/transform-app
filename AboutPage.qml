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
import QtQuick.Window 2.0

import "about.js" as About

Page {
    title: "About"
    TextArea {
        id: aboutTextArea
        width: parent.width
        height: parent.height
        readOnly: true
        text: About.workName + "\n" +
              "Copyright (c) " + About.copyright + "\n" +
              "\n" +
              "Source: <" + About.sourceCodeUrl + ">\n" +
              "\n" +
              "This program comes with ABSOLUTELY NO WARRANTY. This is free software, " +
              "and you are welcome to redistribute it under certain conditions. " +
              "See License (GNU GPL 3) for details.\n" +
              "\n" +
              "Third party libraries:\n" +
              About.libs.join("\n")
    }
}
