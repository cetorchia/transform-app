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

#include "pathextransformer.h"

PathexTransformer::PathexTransformer(QObject *parent) : QObject(parent)
{

}

QStringList PathexTransformer::transform(const QVariantMap& queryElement, const QVariant& inTree)
{
    if (queryElement["pathex"].toString() == "/") {
        QStringList outElementList
        {
            inTree.toString()
        };
        return outElementList;
    } else {
        QStringList pathElements = queryElement["pathex"].toString().split("/", QString::SkipEmptyParts);
        QVariant element = inTree;
        return transform(pathElements, element);
    }
}

QStringList PathexTransformer::transform(const QStringList& pathElements, const QVariant& element)
{
    if (pathElements.size() > 0) {
        QString pathElement = pathElements[0];
        if (!element.toMap().isEmpty()) {
            QVariantMap map = element.toMap();
            if (map.contains(pathElement)) {
                QStringList newPathElements = pathElements;
                newPathElements.removeFirst();
                return transform(newPathElements, map[pathElement]);
            } else {
                return QStringList();
            }
        } else if (!element.toList().isEmpty()) {
            QStringList outElementList;
            if (pathElement == "*") {
                QVariantList list = element.toList();
                QStringList newPathElements = pathElements;
                newPathElements.removeFirst();
                for (QVariant subElement: list) {
                    outElementList << transform(newPathElements, subElement);
                }
            }
            return outElementList;
        } else {
            return QStringList();
        }
    } else {
        QStringList outElementList
        {
            element.toString()
        };
        return outElementList;
    }
}
