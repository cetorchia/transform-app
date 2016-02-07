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
    QStringList allowedFields
    {
        "name",
        "url",
        "query"
    };
    return allowedFields;
}

const QStringList FeedStore::requiredFields() {
    return QStringList();
}

const QStringList FeedStore::allowedQueryFields() {
    QStringList allowedQueryFields
    {
        "pathex",
        "fields",
        "regex",
        "key",
        "keyRegex",
    };
    return allowedQueryFields;
}

bool FeedStore::validate(const QVariantMap& data) {
    if (DataStore::validate(data)) {
        QString name = data["name"].toString();
        if (name.isEmpty()) {
            emit error("Name is required.");
            return false;
        }
        QVariantList query = data["query"].toList();
        if (query.isEmpty()) {
            emit error("Query is required");
            return false;
        }
        for (QVariant var: query) {
            QVariantMap queryElement = var.toMap();
            QStringList allowedQueryFields = this->allowedQueryFields();
            for (QString field: queryElement.keys()) {
                if (!allowedQueryFields.contains(field)) {
                    emit error("Unallowed query field \"" + field + "\"");
                    return false;
                }
            }
            QString pathex = queryElement["pathex"].toString();
            QStringList fields = queryElement["fields"].toStringList();
            QString regex = queryElement["regex"].toString();
            QString key = queryElement["key"].toString();
            QString keyRegex = queryElement["keyRegex"].toString();
            if (fields.isEmpty()) {
                emit error("Field names are required.");
                return false;
            }
            if (pathex.isEmpty()) {
                emit error("Path expression is required.");
                return false;
            }
            if (!regex.isEmpty() && !QRegularExpression(regex).isValid()) {
                emit error("Invalid regular expression: " + regex);
                return false;
            }
            if (!keyRegex.isEmpty() && regex.isEmpty()) {
                emit error("Regular expression is required for key regular expression.");
                return false;
            }
            if (!keyRegex.isEmpty() && key.isEmpty()) {
                emit error("Key field name is required for key regular expression");
                return false;
            }
            if (!keyRegex.isEmpty() && !QRegularExpression(keyRegex).isValid()) {
                emit error("Invalid key regular expression: " + keyRegex);
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}
