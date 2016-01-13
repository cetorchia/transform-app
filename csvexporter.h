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

#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include <QObject>
#include <QVariant>

class CsvExporter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filename MEMBER m_filename NOTIFY filenameChanged)
    Q_PROPERTY(QStringList fields MEMBER m_fields NOTIFY fieldsChanged)
    Q_PROPERTY(QVariantList data MEMBER m_data NOTIFY dataChanged)
public:
    explicit CsvExporter(QObject *parent = 0);

    Q_INVOKABLE void save();
    Q_INVOKABLE void copy();

signals:
    void filenameChanged();
    void fieldsChanged();
    void dataChanged();
    void finished(const QString& path);
    void error(const QString& message);

public slots:
protected:
    QString toCsv();

private:
    QString m_filename;
    QStringList m_fields;
    QVariantList m_data;
};

#endif // CSVEXPORTER_H
