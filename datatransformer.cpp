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

#include <QUrl>

#include "datatransformer.h"

DataTransformer::DataTransformer(QObject *parent) : QObject(parent)
{

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
    QVariantList outData;
    QVariant inTree = treeParser.parseTree(inData);
    for (QVariant var: feedData["query"].toList()) {
        QVariantMap queryElement = var.toMap();
        QStringList queryFields = queryElement["fields"].toStringList();
        QStringList inElementList = pathexTransformer.transform(queryElement, inTree);
        if (!queryElement["regex"].toString().isEmpty()) {
            for (QString inElementText: inElementList) {
                QVariantMap response = regexTransformer.transform(queryElement, inElementText);
                outData += response["data"].toList();
            }
        } else {
            for (QString inElementText: inElementList) {
                QVariantMap datum;
                for (QString field: queryFields) {
                    datum[field] = inElementText;
                };
                outData << datum;
            }
        }
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
    emit finished(fields, outData);
}
