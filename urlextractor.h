#ifndef URLEXTRACTOR_H
#define URLEXTRACTOR_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>

class UrlExtractor : public QObject
{
    Q_OBJECT
public:
    explicit UrlExtractor(QObject *parent = 0);

    void getFromUrl(const QUrl& url, int attempts = 0);

signals:
    void finished(const QString& data);
    void error(const QString& message);

public slots:
protected:
    QNetworkAccessManager qnam;
};

#endif // URLEXTRACTOR_H
