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

#include <QRegularExpression>

#include "queryelementlistmodel.h"

QueryElementListModel::QueryElementListModel(QObject *parent) : QObject(parent)
{

}

QVariantList QueryElementListModel::queryElements()
{
    QVariantList queryElements;
    for (QVariantMap queryElement: m_queryElements.values()) {
        queryElements << queryElement;
    }
    return queryElements;
}

void QueryElementListModel::setQueryElements(const QVariantList& queryElementList)
{
    QMap<QString, QVariantMap> queryElementMap;
    for (QVariant var: queryElementList) {
        QVariantMap queryElement = var.toMap();
        QString pathex = queryElement["pathex"].toString();
        queryElementMap[pathex] = queryElement;
    }
    m_queryElements = queryElementMap;
    emit queryElementsChanged();
}

QVariantMap QueryElementListModel::get(const QString& pathex, const QString& elementName)
{
    if (!m_queryElements.contains(pathex)) {
        return QVariantMap
        {
            {"pathex", pathex},
            {"fields", elementName},
            {"regex", ""},
            {"key", ""},
            {"keyRegex", ""}
        };
    } else {
        QVariantMap existingQueryElement = m_queryElements[pathex];
        QStringList fields = existingQueryElement["fields"].toStringList();
        existingQueryElement["fields"] = fieldsStr(fields);
        return existingQueryElement;
    }
}

void QueryElementListModel::put(const QString& pathex,
                                const QString& fieldsStr,
                                const QString& regex,
                                const QString& key,
                                const QString& keyRegex)
{
    QVariantMap newQueryElement
    {
        {"pathex", pathex},
        {"fields", fields(fieldsStr)},
        {"regex", regex},
        {"key", key},
        {"keyRegex", keyRegex}
    };
    m_queryElements[pathex] = newQueryElement;
    emit queryElementsChanged();
}

QString QueryElementListModel::fieldsStr(const QStringList& fields)
{
    return fields.join(", ");
}

QStringList QueryElementListModel::fields(const QString& fieldsStr)
{
    return fieldsStr.split(QRegularExpression("\\s*,\\s*"), QString::KeepEmptyParts);
}
