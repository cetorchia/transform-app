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
#include "feedstore.h"

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
    if (feedData["type"] == "REGEX") {
        QVariantMap response = regexTransformer.transform(feedData, inData);
        QStringList fields = response["fields"].toStringList();
        QVariantList outData = response["data"].toList();
        emit finished(fields, outData);
    }
}
