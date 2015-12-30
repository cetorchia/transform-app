#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "myobject.h"

MyObject::MyObject()
{
}

QString MyObject::text() const {
    return "Hello, world!";
}

QString MyObject::hello(QString json) {
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject obj = doc.object();
    QString stuff = obj["stuff"].toString();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("transform");
    if (!db.open()) {
        qFatal("Cannot open database");
        return NULL;
    }
    db.exec(QString::fromLatin1("UPDATE temp SET text = '%1'").arg(stuff));
    QSqlQuery query = db.exec("SELECT * FROM temp");
    if (!query.next()) {
        qFatal("Cannot fetch string");
        return NULL;
    }
    QString newStuff = query.value("text").toString();
    QJsonObject newObj;
    newObj.insert("stuff", QJsonValue(newStuff));
    QJsonDocument newDoc(newObj);
    QString newJson(newDoc.toJson());
    return newJson;
}
