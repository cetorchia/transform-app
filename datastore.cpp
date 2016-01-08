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
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "database.h"
#include "datastore.h"

DataStore::DataStore(QObject *parent) : QObject(parent)
{

}

const QString DataStore::tableName() {
    return "";
}

const QString DataStore::createStatement() {
    return "CREATE TABLE IF NOT EXISTS " + this->tableName() + " (id INTEGER PRIMARY KEY, data)";
}

const QString DataStore::insertStatement() {
    return "INSERT INTO " + this->tableName() + "(data) VALUES (:data)";
}

const QString DataStore::updateStatement() {
    return "UPDATE " + this->tableName() + " SET data = :data WHERE id = :id";
}

const QString DataStore::selectStatement() {
    return "SELECT id, data FROM " + this->tableName();
}

const QString DataStore::selectStatementById() {
    return "SELECT id, data FROM " + this->tableName() + " WHERE id = :id";
}

const QString DataStore::deleteStatementById() {
    return "DELETE FROM " + this->tableName() + " WHERE id = :id";
}

const QStringList DataStore::allowedFields() {
    return QStringList();
}

const QStringList DataStore::requiredFields() {
    return QStringList();
}

bool DataStore::validate(QVariantMap data) {
    QStringList existingFields = data.keys();
    QStringList allowedFields = this->allowedFields();
    QStringList requiredFields = this->requiredFields();
    for (int i = 0; i < existingFields.size(); i++) {
        QString field = existingFields.at(i);
        if (!allowedFields.contains(field)) {
            emit error("Unallowed field \"" + field + "\"");
            return false;
        }
    }
    for (int i = 0; i < requiredFields.size(); i++) {
        QString field = requiredFields.at(i);
        if (!existingFields.contains(field)) {
            emit error("Required field \"" + field + "\"");
            return false;
        }
    }
    return true;
}

void DataStore::save(QVariantMap data) {
    if (this->validate(data)){
        QSqlDatabase db = Database::db();
        if (!db.open()) {
            emit error("Cannot open database");
            return;
        }
        QSqlQuery create(db);
        create.prepare(this->createStatement());
        if (!create.exec()) {
            QSqlError sqlError = create.lastError();
            emit error(sqlError.text());
            return;
        }
        QSqlQuery insert(db);
        insert.prepare(this->insertStatement());
        QJsonDocument doc(QJsonObject::fromVariantMap(data));
        insert.bindValue(":data", doc.toJson());
        if (!insert.exec()) {
            QSqlError sqlError = insert.lastError();
            emit error(sqlError.text());
            return;
        }
        emit saved();
    }
}

void DataStore::save(int id, QVariantMap data) {
    if (this->validate(data)){
        QSqlDatabase db = Database::db();
        if (!db.open()) {
            emit error("Cannot open database");
            return;
        }
        QSqlQuery create(db);
        create.prepare(this->createStatement());
        if (!create.exec()) {
            QSqlError sqlError = create.lastError();
            emit error(sqlError.text());
            return;
        }
        QSqlQuery update(db);
        update.prepare(this->updateStatement());
        QJsonDocument doc(QJsonObject::fromVariantMap(data));
        update.bindValue(":id", id);
        update.bindValue(":data", doc.toJson());
        if (!update.exec()) {
            QSqlError sqlError = update.lastError();
            emit error(sqlError.text());
            return;
        }
        emit saved();
    }
}

QVariantMap DataStore::get(int id) {
    QSqlDatabase db = Database::db();
    if (!db.open()) {
        emit error("Cannot open database");
        return QVariantMap();
    }
    QSqlQuery create(db);
    create.prepare(this->createStatement());
    if (!create.exec()) {
        QSqlError sqlError = create.lastError();
        emit error(sqlError.text());
        return QVariantMap();
    }
    QSqlQuery select(db);
    select.prepare(this->selectStatementById());
    select.bindValue(":id", id);
    if (!select.exec()) {
        QSqlError sqlError = select.lastError();
        emit error(sqlError.text());
        return QVariantMap();
    }
    if (select.next()) {
        QString objectData = select.value("data").toString();
        QJsonDocument doc = QJsonDocument::fromJson(objectData.toUtf8());
        QVariantMap object;
        object["id"] = select.value("id").toInt();
        object["data"] = doc.toVariant();
        return object;
    } else {
        emit error(select.lastQuery());
        return QVariantMap();
    }
}

QVariantList DataStore::get() {
    QSqlDatabase db = Database::db();
    if (!db.open()) {
        emit error("Cannot open database");
        return QVariantList();
    }
    QSqlQuery create(db);
    create.prepare(this->createStatement());
    if (!create.exec()) {
        QSqlError sqlError = create.lastError();
        emit error(sqlError.text());
        return QVariantList();
    }
    QSqlQuery select(db);
    select.prepare(this->selectStatement());
    if (!select.exec()) {
        QSqlError sqlError = select.lastError();
        emit error(sqlError.text());
        return QVariantList();
    }
    QVariantList objects;
    while (select.next()) {
        QString objectData = select.value("data").toString();
        QJsonDocument doc = QJsonDocument::fromJson(objectData.toUtf8());
        QVariantMap object;
        object["id"] = select.value("id").toInt();
        object["data"] = doc.toVariant();
        objects.append(object);
    }
    return objects;
}

void DataStore::remove(int id) {
    QSqlDatabase db = Database::db();
    if (!db.open()) {
        emit error("Cannot open database");
        return;
    }
    QSqlQuery create(db);
    create.prepare(this->createStatement());
    if (!create.exec()) {
        QSqlError sqlError = create.lastError();
        emit error(sqlError.text());
        return;
    }
    QSqlQuery query(db);
    query.prepare(this->deleteStatementById());
    query.bindValue(":id", id);
    if (!query.exec()) {
        QSqlError sqlError = query.lastError();
        emit error(sqlError.text());
        return;
    }
    emit deleted();
}
