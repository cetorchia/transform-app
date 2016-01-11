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

#include <functional>
#include <QObject>
#include <QVariant>
#include <QNetworkAccessManager>

#include "regextransformer.h"

class DataTransformer : public QObject
{
    Q_OBJECT
public:
    explicit DataTransformer(QObject *parent = 0);

    Q_INVOKABLE void transform(const QVariantMap& feedData, const QString& inData);
    Q_INVOKABLE void transform(const QVariantMap& feedData);

signals:
    void finished(const QStringList& outFields, const QVariantList& outData);
    void error(const QString& message);

public slots:
private slots:
protected:
    QNetworkAccessManager qnam;
    RegexTransformer regexTransformer;
private:
    void getFromUrl(const QUrl& url, std::function<void (const QString&)>, int attempts = 0);
};

#endif // DATATRANSFORMER_H
