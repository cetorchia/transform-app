#include <QRegularExpression>

#include "regextransformer.h"

RegexTransformer::RegexTransformer(QObject *parent) : QObject(parent)
{

}

QVariantMap RegexTransformer::transform(const QVariantMap& feedData, const QString& inData)
{
    QRegularExpression re(feedData["regex"].toString(),
            QRegularExpression::MultilineOption);
    QStringList outFields = fields(feedData["regexFields"].toString());
    QVariantList outData;
    QRegularExpressionMatchIterator i = re.globalMatch(inData);
    while (i.hasNext()) {
        QVariantMap datum;
        QRegularExpressionMatch match = i.next();
        QStringList capturedTexts = match.capturedTexts();
        if (capturedTexts.length() == 1) {
            // Return whole match, not captured groups
            datum[outFields[0]] = capturedTexts[0];
        } else {
            // Return only captured groups
            for (int j = 1; j < capturedTexts.length() && j <= outFields.length(); j++) {
                datum[outFields[j - 1]] = capturedTexts[j];
            }
        }
        outData << datum;
    }
    QString keyField = feedData["key"].toString();
    if (outFields.removeOne(keyField)) {
        outFields.insert(0, keyField);
    }
    QVariantMap response
    {
        {"fields", outFields},
        {"data", outData}
    };
    return response;
}

QStringList RegexTransformer::fields(const QString& fieldsString)
{
    QRegularExpression splitRe("\\s*,\\s*");
    return fieldsString.split(splitRe, QString::SkipEmptyParts);
}
