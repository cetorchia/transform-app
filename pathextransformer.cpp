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

QMap<QString, QString> PathexTransformer::transform(const QVariantMap& queryElement, const QVariant& inTree)
{
    if (queryElement["pathex"].toString() == "/") {
        QMap<QString, QString> outElementMap
        {
            {"/", inTree.toString()}
        };
        return outElementMap;
    } else {
        QStringList queryPathComponents = this->pathComponents(queryElement["pathex"].toString());
        QVariant element = inTree;
        return transform(queryPathComponents, "/", element);
    }
}

QMap<QString, QString> PathexTransformer::transform(const QStringList& queryPathComponents,
                                                    const QString& elementPath,
                                                    const QVariant& element)
{
    if (queryPathComponents.size() > 0) {
        QString queryPathComponent = queryPathComponents[0];
        if (!element.toMap().isEmpty()) {
            QVariantMap map = element.toMap();
            if (map.contains(queryPathComponent)) {
                QStringList newQueryPathComponents = queryPathComponents;
                newQueryPathComponents.removeFirst();
                QString newElementPath = elementPath + queryPathComponent + "/";
                return transform(newQueryPathComponents, newElementPath, map[queryPathComponent]);
            } else {
                return QMap<QString, QString>();
            }
        } else if (!element.toList().isEmpty()) {
            QMap<QString, QString> outElementMap;
            if (queryPathComponent == "*") {
                QVariantList list = element.toList();
                QStringList newQueryPathComponents = queryPathComponents;
                newQueryPathComponents.removeFirst();
                for (int i = 0; i < list.size(); i++) {
                    QVariant newElement = list[i];
                    QString newElementPath = elementPath + QString::number(i) + "/";
                    QMap<QString, QString> newElementMap = transform(newQueryPathComponents, newElementPath, newElement);
                    outElementMap.unite(newElementMap);
                }
            }
            return outElementMap;
        } else {
            return QMap<QString, QString>();
        }
    } else {
        QMap<QString, QString> outElementMap
        {
            {elementPath, element.toString()}
        };
        return outElementMap;
    }
}

void PathexTransformer::addElementData(QMap<QString, QList<QVariantMap>>& outDataMap,
                                       const QVariantMap& queryElement,
                                       const QMap<QString, QList<QVariantMap>>& newElementDataMap)
{
    if (queryElement["pathex"].toString() == "/") {
        outDataMap = newElementDataMap;
    } else {
        QStringList queryPathComponents = this->pathComponents(queryElement["pathex"].toString());
        for (QString elementPath: newElementDataMap.keys()) {
            QList<QVariantMap> newElementDataList = newElementDataMap[elementPath];
            QString elementKey = this->elementKey(queryPathComponents, elementPath);
            if (!outDataMap.contains(elementKey)) {
                outDataMap[elementKey] = newElementDataList;
            } else {
                QList<QVariantMap> elementDataList = outDataMap[elementKey];
                QList<QVariantMap> outElementDataList;
                for (QVariantMap datum: elementDataList) {
                    for (QVariantMap newDatum: newElementDataList) {
                        QVariantMap outDatum = datum;
                        outDatum.unite(newDatum);
                        outElementDataList << outDatum;
                    }
                }
                outDataMap[elementKey] = outElementDataList;
            }
        }
    }
}

QStringList PathexTransformer::pathComponents(const QString& pathex)
{
    QStringList pathComponents = pathex.split("/", QString::SkipEmptyParts);
    return pathComponents;
}

QString PathexTransformer::elementKey(const QStringList& queryPathComponents, const QString& elementPath)
{
    QStringList elementPathComponents = this->pathComponents(elementPath);
    for (int i = elementPathComponents.size() - 1; i >= 0; i--) {
        if (queryPathComponents[i] == "*") {
            break;
        } else {
            elementPathComponents.removeAt(i);
        }
    }
    QString elementKey;
    if (elementPathComponents.size() == 0) {
        elementKey = "/";
    } else {
        elementKey = "/" + elementPathComponents.join("/") + "/";
    }
    return elementKey;
}
