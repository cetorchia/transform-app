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

function escapeObject(object) {
    var escapedObject = {};
    Object.keys(object).forEach(function (field) {
        if (typeof object[field] === "string") {
            var str = object[field];
            var isUrl = (/^https?:\/\//.test(str) ? true : false);
            if (isUrl) {
                escapedObject[field] = "<a href=\"" + str + "\">" + str + "</a>";
            } else {
                escapedObject[field] = htmlEntities(str);
            }
        }
    });
    return escapedObject;
}

/**
 * htmlEntities()
 * https://css-tricks.com/snippets/javascript/htmlentities-for-javascript/
 */
function htmlEntities(str) {
    return String(str).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;');
}
