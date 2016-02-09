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

#ifndef PATHEXTRANSFORMER_H
#define PATHEXTRANSFORMER_H

#include <QObject>
#include <QVariant>

class PathexTransformer : public QObject
{
    Q_OBJECT
public:
    explicit PathexTransformer(QObject *parent = 0);

    QMap<QString, QString> transform(const QVariantMap& queryElement, const QVariant& inTree);
    QMap<QString, QString> transform(const QStringList& queryPathComponents, const QString& elementPath, const QVariant& element);
    void addElementData(QMap<QString, QList<QVariantMap>>& outDataMap,
                        const QVariantMap& queryElement,
                        const QMap<QString, QList<QVariantMap>>& newElementDataMap);
signals:

public slots:
private:
    QStringList pathComponents(const QString& pathex);
    QString elementKey(const QStringList& queryPathComponents, const QString& elementPath);
};

#endif // PATHEXTRANSFORMER_H
