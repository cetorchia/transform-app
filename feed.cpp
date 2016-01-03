#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "feed.h"

Feed::Feed()
{

}

bool Feed::validate(QString data) {
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.object();
    QString name = obj["name"].toString();
    QString type = obj["type"].toString();
    QString regex = obj["regex"].toString();
    QString regexFields = obj["regexFields"].toString();
    QString xmlPathex = obj["xmlPathex"].toString();
    QString jsonPathex = obj["jsonPathex"].toString();
    if (name.isEmpty()) {
        emit error(QString("Name is required."));
        return false;
    } else if (type == "REGEX" && regex.isEmpty()) {
        emit error(QString("Regular expression is required."));
        return false;
    } else if (type == "REGEX" && regexFields.isEmpty()) {
        emit error(QString("Fields are required."));
        return false;
    } else if (type == "XML_PATHEX" && xmlPathex.isEmpty()) {
        emit error(QString("Path expression is required."));
        return false;
    } else if (type == "JSON_PATHEX" && jsonPathex.isEmpty()) {
        emit error(QString("Path expression is required."));
        return false;
    } else {
        return true;
    }
}

void Feed::save(QString data) {
    if (validate(data)){
        emit saved();
    }
}

QString Feed::load(int id) {
    return NULL;
}
