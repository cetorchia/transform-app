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
import QtQuick.Layouts 1.1

Item {
    id: self
    signal clicked
    width: Screen.height / 20
    height: width
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            self.clicked();
        }
        onEntered: {
            rect.color = rect.hoverColour;
        }
        onExited: {
            rect.color = rect.normalColour;
        }
        onPressed: {
            rect.color = rect.pressedColour;
        }
        onReleased: {
            rect.color = rect.normalColour;
        }
    }
    Rectangle {
        id: rect
        anchors.fill: parent
        property string normalColour: "#f8f8f8"
        property string hoverColour: "#d8d8d8"
        property string pressedColour: "#b8b8b8"
        color: normalColour
        border.color: "#a0a0a0"
        radius: 3
    }
}
