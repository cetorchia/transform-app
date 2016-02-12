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

#include <QApplication>
#include <QClipboard>
#include <QSaveFile>
#include <QStandardPaths>

#include "csvexporter.h"

CsvExporter::CsvExporter(QObject *parent) : QObject(parent)
{

}

void CsvExporter::save()
{
    QStringList downloadPaths = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
    QString downloadPath = downloadPaths[0];
    QString path = downloadPath + "/" + m_filename;
    QSaveFile saveFile(path);
    saveFile.open(QIODevice::WriteOnly);
    saveFile.write(toCsv().toUtf8());
    if (saveFile.commit()) {
        emit finished(path);
    } else {
        emit error("Could not save " + path);
    }
}

void CsvExporter::copy()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(toCsv());
}

QString CsvExporter::toCsv()
{
    QString csv;
    QStringList formattedFields;
    for (QString field: m_fields) {
        formattedFields << "\"" + field.replace('\"', "\"\"") + "\"";
    }
    csv += formattedFields.join(',') + '\n';
    for (QVariant var: m_data) {
        QVariantMap datum = var.toMap();
        QStringList formattedValues;
        for (QString field: m_fields) {
            formattedValues << "\"" + datum[field].toString().replace('\"', "\"\"") + "\"";
        }
        csv += formattedValues.join(',') + '\n';
    }
    return csv;
}
