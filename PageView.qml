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
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

StackView {
    property var params
    property var title: if (currentItem && currentItem.title) {
                            currentItem.title
                        } else {
                            ""
                        }
    anchors.fill: parent
    // Implements back key navigation
    focus: true
    Keys.onReleased: if (event.key === Qt.Key_Back && depth > 1) {
                         pop();
                         event.accepted = true;
                     }
    function goTo(qmlFile, newParams) {
        push(Qt.resolvedUrl(qmlFile));
        if (newParams) {
            params = newParams;
        } else {
            params = {};
        }
    }
    function closePage() {
        pop();
        params = {};
    }
    function clearPages() {
        clear();
        params = {};
    }
    function parameters() {
        return params;
    }
}
