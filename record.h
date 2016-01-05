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

#ifndef RECORD_H
#define RECORD_H

#include <QObject>

class Record : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void save(QString data);
    Q_INVOKABLE void save(int id, QString data);
    Q_INVOKABLE QString load(int id);

    virtual const QStringList requiredFields();
    virtual const QStringList allowedFields();
    virtual bool validate(QString data);

protected:
    explicit Record(QObject *parent = 0);

signals:
    void saved();
    void error(QString message);

public slots:
};

#endif // RECORD_H
