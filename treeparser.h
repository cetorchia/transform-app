#ifndef TREEPARSER_H
#define TREEPARSER_H

#include <QObject>
#include <QVariant>

class TreeParser
{
public:
    TreeParser();

    QVariant parseTree(const QString& inData);
signals:

public slots:
};

#endif // TREEPARSER_H
