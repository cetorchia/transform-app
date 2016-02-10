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

#include <QJsonDocument>

#include "treeparser.h"

TreeParser::TreeParser(QObject *parent) : QObject(parent)
{

}

QVariant TreeParser::parseTree(const QString& inData)
{
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(inData.toUtf8(), &error);
    if (!error.error) {
        return jsonDoc.toVariant();
    }
    QDomDocument xmlDoc;
    xmlDoc.setContent(inData);
    if (!xmlDoc.isNull()) {
        return toVariant(xmlDoc.documentElement());
    }
    return inData;
}

QVariant TreeParser::toVariant(const QDomElement& domElement)
{
    bool hasChildElements = !domElement.firstChildElement().isNull();
    if (hasChildElements || domElement.hasAttributes()) {
        QVariantMap elementMap;
        QDomNamedNodeMap attributes = domElement.attributes();
        for (int i = 0; i < attributes.size(); i++) {
            QDomAttr domAttr = attributes.item(i).toAttr();
            QString name = "@" + domAttr.name();
            QString value = domAttr.value();
            elementMap[name] = value;
        }
        QDomNode node = domElement.firstChild();
        while (!node.isNull()) {
            if (node.isText()) {
                QDomText domText = node.toText();
                QString name = "text";
                QString value = domText.data();
                elementMap[name] = value;
            } else if (node.isElement()) {
                QDomElement childDomElement = node.toElement();
                QString name = childDomElement.tagName();
                if (!elementMap.contains(name)) {
                    elementMap[name] = toVariant(childDomElement);
                } else if (elementMap[name].toList().isEmpty()){
                    QVariantList elementList
                    {
                        elementMap[name],
                        toVariant(childDomElement)
                    };
                    elementMap[name] = elementList;
                } else {
                    QVariantList elementList = elementMap[name].toList();
                    elementList << toVariant(childDomElement);
                    elementMap[name] = elementList;
                }
            }
            node = node.nextSibling();
        }
        return elementMap;
    } else if (!domElement.text().isEmpty()) {
        return domElement.text();
    } else {
        return QVariant();
    }
}
