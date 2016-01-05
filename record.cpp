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
#include "record.h"

Record::Record(QObject *parent) : QObject(parent)
{

}

const QString Record::tableName() {
    return "";
}

const QString Record::createStatement() {
    return "CREATE TABLE IF NOT EXISTS " + this->tableName() + " (id INTEGER PRIMARY KEY, data)";
}

const QString Record::insertStatement() {
    return "INSERT INTO " + this->tableName() + "(data) VALUES (:data)";
}

const QStringList Record::allowedFields() {
    return QStringList();
}

const QStringList Record::requiredFields() {
    return QStringList();
}

bool Record::validate(QString data) {
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.object();
    QStringList existingFields = obj.keys();
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

void Record::save(QString data) {
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
        insert.bindValue(":data", QVariant(data));
        if (!insert.exec()) {
            QSqlError sqlError = insert.lastError();
            emit error(sqlError.text());
            return;
        }
        emit saved();
    }
}

void Record::save(int id, QString data) {
    if (this->validate(data)){
        emit saved();
    }
}

QString Record::load(int id) {
    return NULL;
}
