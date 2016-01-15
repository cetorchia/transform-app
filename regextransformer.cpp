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

#include <QRegularExpression>

#include "regextransformer.h"

RegexTransformer::RegexTransformer(QObject *parent) : QObject(parent)
{

}

QVariantMap RegexTransformer::transform(const QVariantMap& queryElement, const QString& inData)
{
    QRegularExpression re(queryElement["regex"].toString(),
            QRegularExpression::MultilineOption);
    QVariantList outData;
    QString keyField = queryElement["key"].toString();
    QString keyRegex = queryElement["keyRegex"].toString();
    QStringList fields = queryElement["fields"].toStringList();
    if (!keyField.isEmpty() && !keyRegex.isEmpty()) {
        QRegularExpression keyRe(keyRegex);
        QRegularExpressionMatchIterator i = keyRe.globalMatch(inData);
        if (i.hasNext()) {
            QStringList inDataLists = inData.split(keyRe, QString::KeepEmptyParts);
            matchData(outData, re, fields, inDataLists.first());
            for (int j = 1; j < inDataLists.length(); j++) {
                QRegularExpressionMatch match = i.next();
                QString keyValue = match.captured();
                QString inSubData = inDataLists[j];
                QVariantList outSubData;
                matchData(outSubData, re, fields, inSubData);
                for (QVariant var: outSubData) {
                    QVariantMap datum = var.toMap();
                    datum[keyField] = keyValue;
                    outData << datum;
                }
            }
        } else {
            matchData(outData, re, fields, inData);
        }
    } else {
        matchData(outData, re, fields, inData);
    }
    QVariantMap response
    {
        {"fields", fields},
        {"data", outData}
    };
    return response;
}

void RegexTransformer::matchData(QVariantList& outData, const QRegularExpression& re, const QStringList& fields, const QString& inData)
{
    QRegularExpressionMatchIterator i = re.globalMatch(inData);
    while (i.hasNext()) {
        QVariantMap datum;
        QRegularExpressionMatch match = i.next();
        QStringList capturedTexts = match.capturedTexts();
        if (capturedTexts.length() == 1) {
            // Return whole match, not captured groups
            datum[fields[0]] = capturedTexts[0];
        } else {
            // Return only captured groups
            for (int j = 1; j < capturedTexts.length() && j <= fields.length(); j++) {
                datum[fields[j - 1]] = capturedTexts[j];
            }
        }
        outData << datum;
    }
}
