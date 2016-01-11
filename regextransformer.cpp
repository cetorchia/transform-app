#include <QRegularExpression>

#include "regextransformer.h"

RegexTransformer::RegexTransformer(QObject *parent) : QObject(parent)
{

}

QVariantMap RegexTransformer::transform(const QVariantMap& feedData, const QString& inData)
{
    QRegularExpression re(feedData["regex"].toString(),
            QRegularExpression::MultilineOption);
    QStringList fields = parseFields(feedData["regexFields"].toString());
    QVariantList outData;
    QString keyField = feedData["key"].toString();
    QString keyRegex = feedData["keyRegex"].toString();
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
    if (!keyField.isEmpty()) {
        fields.removeOne(keyField);
        fields.insert(0, keyField);
    }
    QVariantMap response
    {
        {"fields", fields},
        {"data", outData}
    };
    return response;
}

QStringList RegexTransformer::parseFields(const QString& fieldsString)
{
    QRegularExpression splitRe("\\s*,\\s*");
    return fieldsString.split(splitRe, QString::SkipEmptyParts);
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
