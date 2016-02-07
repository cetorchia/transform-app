#include "pathextransformer.h"

PathexTransformer::PathexTransformer(QObject *parent) : QObject(parent)
{

}

QStringList PathexTransformer::transform(const QVariantMap& queryElement, const QVariant& inTree)
{
    if (queryElement["pathex"].toString() == "/") {
        QStringList list
        {
            inTree.toString()
        };
        return list;
    } else {
        return QStringList();
    }
}
