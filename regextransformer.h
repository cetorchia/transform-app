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

#ifndef REGEXTRANSFORMER_H
#define REGEXTRANSFORMER_H

#include <QObject>
#include <QVariant>

class RegexTransformer : public QObject
{
    Q_OBJECT
public:
    explicit RegexTransformer(QObject *parent = 0);

    QVariantMap transform(const QVariantMap& feedData, const QString& inData);
signals:

public slots:
private:
    QStringList parseFields(const QString& fieldsString);
    void matchData(QVariantList& outData, const QRegularExpression& re, const QStringList& fields, const QString& inData);
};

#endif // REGEXTRANSFORMER_H
