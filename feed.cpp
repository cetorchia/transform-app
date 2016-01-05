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

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "record.h"
#include "feed.h"

Feed::Feed(QObject *parent) : Record(parent)
{

}

const QStringList Feed::allowedFields() {
    QStringList allowedFields = QStringList();
    allowedFields << "name"
                  << "type"
                  << "url"
                  << "key"
                  << "keyRegex"
                  << "regex"
                  << "regexFields"
                  << "xmlPathex"
                  << "jsonPathex";
    return allowedFields;
}

const QStringList Feed::requiredFields() {
    return QStringList();
}

bool Feed::validate(QString data) {
    if (Record::validate(data)) {
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject obj = doc.object();
        QString name = obj["name"].toString();
        QString type = obj["type"].toString();
        QString regex = obj["regex"].toString();
        QString regexFields = obj["regexFields"].toString();
        QString xmlPathex = obj["xmlPathex"].toString();
        QString jsonPathex = obj["jsonPathex"].toString();
        if (name.isEmpty()) {
            emit error(QString("Name is required."));
            return false;
        } else if (type == "REGEX" && regex.isEmpty()) {
            emit error(QString("Regular expression is required."));
            return false;
        } else if (type == "REGEX" && regexFields.isEmpty()) {
            emit error(QString("Fields are required."));
            return false;
        } else if (type == "XML_PATHEX" && xmlPathex.isEmpty()) {
            emit error(QString("Path expression is required."));
            return false;
        } else if (type == "JSON_PATHEX" && jsonPathex.isEmpty()) {
            emit error(QString("Path expression is required."));
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}
