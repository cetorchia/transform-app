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
    QStringList fields(const QString& fieldsString);
};

#endif // REGEXTRANSFORMER_H
