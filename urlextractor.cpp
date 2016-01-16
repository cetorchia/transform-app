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

#include <QNetworkRequest>
#include <QNetworkReply>

#include "urlextractor.h"

UrlExtractor::UrlExtractor(QObject *parent) : QObject(parent)
{

}

void UrlExtractor::getFromUrl(const QUrl& url, int attempts)
{
    if (attempts < 10) {
        QNetworkReply *reply = qnam.get(QNetworkRequest(QUrl(url)));
        connect(reply, &QNetworkReply::finished, [=]() {
            QString data(reply->readAll());
            reply->deleteLater();
            QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
            if (reply->error() != QNetworkReply::NoError) {
                emit error("Network error: " + reply->errorString());
            } else if (!redirectionTarget.isNull()) {
                getFromUrl(redirectionTarget.toUrl(), attempts + 1);
            } else {
                emit finished(data);
            }
        });
    } else {
        emit error("Network error: redirect loop");
    }
}
