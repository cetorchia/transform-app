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

Item {
    property string title
    property var params: if (parent.params) {
                             parent.params
                         } else {
                             Object.create(null)
                         }
    function goTo(qmlFile, parameters) {
        if (parent.goTo) {
            parent.goTo(qmlFile, parameters);
        }
    }
    function closePage() {
        if (parent.closePage) {
            parent.closePage();
        }
    }
    function clearPages() {
        if (parent.clearPages) {
            parent.clearPages();
        }
    }
}
