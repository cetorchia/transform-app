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

#include <functional>
#include <QUrl>

#include "datatransformer.h"

DataTransformer::DataTransformer(QObject *parent) : QObject(parent)
{
    connect(this, &DataTransformer::dataChanged, &DataTransformer::escapeData);
}

void DataTransformer::transform(const QVariantMap& feedData)
{
    QUrl url = feedData["url"].toUrl();
    if (url.isValid()) {
        urlExtractor.getFromUrl(url);
        connect(&urlExtractor, &UrlExtractor::finished, [=](const QString& inData) {
            transform(feedData, inData);
        });
        connect(&urlExtractor, &UrlExtractor::error, [=](const QString& message) {
            emit error(message);
        });
    } else {
        emit error("No way to get the data. Is the URL you specified invalid?");
    }
}

void DataTransformer::transform(const QVariantMap& feedData, const QString& inData)
{
    QStringList fields;
    QVariant inTree = treeParser.parseTree(inData);
    QMap<QString, QList<QVariantMap>> outDataMap;
    for (QVariant var: feedData["query"].toList()) {
        QVariantMap queryElement = var.toMap();
        QStringList queryFields = queryElement["fields"].toStringList();
        QMap<QString, QString> inElementMap = pathexTransformer.transform(queryElement, inTree);
        QMap<QString, QList<QVariantMap>> outElementDataMap;
        if (!queryElement["regex"].toString().isEmpty()) {
            for (QString elementPath: inElementMap.keys()) {
                QString inElementText = inElementMap[elementPath];
                QList<QVariantMap> innerDataList = regexTransformer.transform(queryElement, inElementText);
                outElementDataMap[elementPath] = innerDataList;
            }
        } else {
            for (QString elementPath: inElementMap.keys()) {
                QString inElementText = inElementMap[elementPath];
                QVariantMap datum;
                for (QString field: queryFields) {
                    datum[field] = inElementText;
                }
                QList<QVariantMap> innerDataList {datum};
                outElementDataMap[elementPath] = innerDataList;
            }
        }
        pathexTransformer.addElementData(outDataMap, queryElement, outElementDataMap);
        // Maintain the list of field names
        QString keyField = queryElement["key"].toString();
        if (!keyField.isEmpty()) {
            queryFields.removeOne(keyField);
            queryFields.insert(0, keyField);
        }
        for (QString field: queryFields) {
            if (!fields.contains(field)) {
                fields.append(field);
            }
        }
    }
    QList<QVariantMap> outDataList = flatten(outDataMap);
    QVariantList outData = toVariantList(outDataList);
    m_fields = fields;
    m_data = outData;
    emit fieldsChanged();
    emit dataChanged();
}

QList<QVariantMap> DataTransformer::flatten(const QMap<QString, QList<QVariantMap>>& dataMap)
{
    QList<QVariantMap> outList;
    for (QString key: dataMap.keys()) {
        QList<QVariantMap> dataList = dataMap[key];
        outList += dataList;
    }
    return outList;
}

QVariantList DataTransformer::toVariantList(const QList<QVariantMap>& dataList)
{
    QVariantList variantList;
    for (QVariantMap datum: dataList) {
        variantList << datum;
    }
    return variantList;
}

void DataTransformer::escapeData()
{
    QVariantList outData;
    for (QVariant var: m_data) {
        QVariantMap datum = var.toMap();
        QUrl firstUrl;
        for (QString field: datum.keys()) {
            QUrl url = datum[field].toUrl();
            if (url.isValid() && (url.scheme() == "http" || url.scheme() == "https")) {
                QString str = "<a href=\"" + url.toString() + "\">" + url.toString() + "</a>";
                datum[field] = str;
                if (firstUrl.isEmpty()) {
                    firstUrl = url;
                }
            } else {
                QString str = datum[field].toString();
                if (!str.isEmpty()) {
                    str.replace("&", "&amp;");
                    str.replace("<", "&lt;");
                    str.replace(">", "&gt;");
                    str.replace("\"", "&quot;");
                    datum[field] = str;
                }
            }
        }
        if (!firstUrl.isEmpty()) {
            datum["__url"] = firstUrl.toString();
        }
        outData << datum;
    }
    m_escapedData = outData;
    emit escapedDataChanged();
}
