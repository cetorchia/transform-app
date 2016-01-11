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
