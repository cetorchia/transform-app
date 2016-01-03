#ifndef FEED_H
#define FEED_H

#include <QObject>

class Feed : public QObject
{
    Q_OBJECT

public:
    Feed();

    Q_INVOKABLE void save(QString data);
    Q_INVOKABLE QString load(int id);

signals:
    void saved();
    void error(QString message);

public slots:

private:
    bool validate(QString data);
};

#endif // FEED_H
