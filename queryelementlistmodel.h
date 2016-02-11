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

#ifndef QUERYELEMENTLISTMODEL_H
#define QUERYELEMENTLISTMODEL_H

#include <QObject>
#include <QVariant>

class QueryElementListModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList queryElements READ queryElements WRITE setQueryElements NOTIFY queryElementsChanged)
public:
    explicit QueryElementListModel(QObject *parent = 0);

    QVariantList queryElements();
    void setQueryElements(const QVariantList& queryElements);

    Q_INVOKABLE QVariantMap get(const QString& pathex, const QString& elementName);
    Q_INVOKABLE void put(const QString& pathex, const QString& fieldsStr, const QString& regex, const QString& key, const QString& keyRegex);

signals:
    void queryElementsChanged();

public slots:
private:
    QMap<QString, QVariantMap> m_queryElements;

    QString fieldsStr(const QStringList& fields);
    QStringList fields(const QString& fieldsStr);
};

#endif // QUERYELEMENTLISTMODEL_H
