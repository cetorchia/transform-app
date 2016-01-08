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

#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QVariant>
#include <QSqlDatabase>

class DataStore : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void save(QVariantMap data);
    Q_INVOKABLE void save(int id, QVariantMap data);
    Q_INVOKABLE QVariantMap get(int id);
    Q_INVOKABLE QVariantList get();
    Q_INVOKABLE void remove(int id);

    virtual const QStringList requiredFields();
    virtual const QStringList allowedFields();
    virtual bool validate(QVariantMap data);

    virtual const QString tableName();
    virtual const QString createStatement();
    virtual const QString insertStatement();
    virtual const QString updateStatement();
    virtual const QString selectStatement();
    virtual const QString selectStatementById();
    virtual const QString deleteStatementById();

protected:
    explicit DataStore(QObject *parent = 0);

signals:
    void saved();
    void deleted();
    void error(QString message);

public slots:

private:
};

#endif // DATASTORE_H
