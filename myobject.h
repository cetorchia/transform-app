#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text)

public:
    MyObject();
    QString text() const;
    Q_INVOKABLE QString hello(QString json);

signals:

public slots:
};

#endif // MYOBJECT_H
