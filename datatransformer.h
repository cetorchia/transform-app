#ifndef DATATRANSFORMER_H
#define DATATRANSFORMER_H

#include <QObject>
#include <QVariant>

class DataTransformer : public QObject
{
    Q_OBJECT
public:
    explicit DataTransformer(QObject *parent = 0);

    Q_INVOKABLE QVariantMap transform(const QString& data);
    Q_INVOKABLE QVariantMap transform();

signals:
    void error(const QString& message);

public slots:
};

#endif // DATATRANSFORMER_H
