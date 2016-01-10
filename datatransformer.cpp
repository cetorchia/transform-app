#include "datatransformer.h"

DataTransformer::DataTransformer(QObject *parent) : QObject(parent)
{

}

QVariantMap DataTransformer::transform(const QString& data)
{
    QStringList fields;
    QVariantList transformed_data;
    QVariantMap data1;
    data1["field1"] = "value1";
    data1["field2"] = "value2";
    QVariantMap data2;
    data2["field1"] = "value3";
    data2["field2"] = "value4";
    fields << "field1" << "field2";
    transformed_data << data1 << data2;
    QVariantMap response;
    response["fields"] = fields;
    response["data"] = transformed_data;
    return response;
}

QVariantMap DataTransformer::transform()
{
    return transform("");
}
