#ifndef PATHEXTRANSFORMER_H
#define PATHEXTRANSFORMER_H

#include <QObject>
#include <QVariant>

class PathexTransformer : public QObject
{
    Q_OBJECT
public:
    explicit PathexTransformer(QObject *parent = 0);

    QStringList transform(const QVariantMap& queryElement, const QVariant& inTree);
signals:

public slots:
};

#endif // PATHEXTRANSFORMER_H
