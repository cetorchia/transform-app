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

#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QRegularExpression>

#include "datastore.h"
#include "feedstore.h"

FeedStore::FeedStore(QObject *parent) : DataStore(parent)
{

}

const QString FeedStore::tableName() {
    return "feed";
}

const QStringList FeedStore::allowedFields() {
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

const QStringList FeedStore::requiredFields() {
    return QStringList();
}

bool FeedStore::validate(const QVariantMap& data) {
    if (DataStore::validate(data)) {
        QString name = data["name"].toString();
        QString type = data["type"].toString();
        QString regex = data["regex"].toString();
        QString keyRegex = data["keyRegex"].toString();
        QString regexFields = data["regexFields"].toString();
        QString xmlPathex = data["xmlPathex"].toString();
        QString jsonPathex = data["jsonPathex"].toString();
        if (name.isEmpty()) {
            emit error("Name is required.");
            return false;
        } else if (type == "REGEX" && regex.isEmpty()) {
            emit error("Regular expression is required.");
            return false;
        } else if (type == "REGEX" && !regex.isEmpty() && !QRegularExpression(regex).isValid()) {
            emit error("Invalid regular expression: " + regex);
            return false;
        } else if (type == "REGEX" && !keyRegex.isEmpty() && !QRegularExpression(keyRegex).isValid()) {
            emit error("Invalid key regular expression: " + keyRegex);
            return false;
        } else if (type == "REGEX" && regexFields.isEmpty()) {
            emit error("Fields are required.");
            return false;
        } else if (type == "XML_PATHEX" && xmlPathex.isEmpty()) {
            emit error("Path expression is required.");
            return false;
        } else if (type == "JSON_PATHEX" && jsonPathex.isEmpty()) {
            emit error("Path expression is required.");
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}
