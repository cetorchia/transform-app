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
#include <QNetworkRequest>
#include <QNetworkReply>

#include "datatransformer.h"
#include "feedstore.h"

DataTransformer::DataTransformer(QObject *parent) : QObject(parent)
{

}

void DataTransformer::transform(const QVariantMap& feedData)
{
    QUrl url = feedData["url"].toUrl();
    if (url.isValid()) {
        getFromUrl(url, [=](const QString& inData) {
            transform(feedData, inData);
        });
    } else {
        emit error("No way to get the data. Is the URL you specified invalid?");
    }
}

void DataTransformer::transform(const QVariantMap& feedData, const QString& inData)
{
    QStringList fields;
    QVariantList transformedData;
    QVariantMap data1;
    data1["field1"] = "value1";
    data1["field2"] = "value2";
    QVariantMap data2;
    data2["field1"] = "value3";
    data2["field2"] = inData;
    fields << "field1" << "field2";
    transformedData << data1 << data2;
    finished(fields, transformedData);
}

void DataTransformer::getFromUrl(const QUrl& url, std::function<void (const QString&)> finished, int attempts)
{
    if (attempts < 10) {
        QNetworkReply *reply = qnam.get(QNetworkRequest(QUrl(url)));
        connect(reply, &QNetworkReply::finished, [=]() {
            QString inData(reply->readAll());
            reply->deleteLater();
            QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
            if (reply->error() != QNetworkReply::NoError) {
                emit error("Network error: " + reply->errorString());
            } else if (!redirectionTarget.isNull()) {
                getFromUrl(redirectionTarget.toUrl(), finished, attempts + 1);
            } else {
                finished(inData);
            }
        });
    } else {
        emit error("Network error: redirect loop");
    }
}
