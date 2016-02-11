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

#ifndef DATATRANSFORMER_H
#define DATATRANSFORMER_H

#include <QObject>
#include <QVariant>

#include "treeparser.h"
#include "pathextransformer.h"
#include "regextransformer.h"
#include "urlextractor.h"

class DataTransformer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList fields MEMBER m_fields NOTIFY fieldsChanged)
    Q_PROPERTY(QVariantList data MEMBER m_data NOTIFY dataChanged)
    Q_PROPERTY(QVariantList escapedData MEMBER m_escapedData NOTIFY escapedDataChanged)
public:
    explicit DataTransformer(QObject *parent = 0);

    Q_INVOKABLE void transform(const QVariantMap& feedData, const QString& inData);
    Q_INVOKABLE void transform(const QVariantMap& feedData);

signals:
    void error(const QString& message);
    void fieldsChanged();
    void dataChanged();
    void escapedDataChanged();

public slots:
private slots:
    void escapeData();
protected:
    QStringList m_fields;
    QVariantList m_data;
    QVariantList m_escapedData;
private:
    TreeParser treeParser;
    PathexTransformer pathexTransformer;
    RegexTransformer regexTransformer;
    UrlExtractor urlExtractor;
    QList<QVariantMap> flatten(const QMap<QString, QList<QVariantMap>>& map);
    QVariantList toVariantList(const QList<QVariantMap>& dataList);
};

#endif // DATATRANSFORMER_H
