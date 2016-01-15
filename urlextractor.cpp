#include <QNetworkRequest>
#include <QNetworkReply>

#include "urlextractor.h"

UrlExtractor::UrlExtractor(QObject *parent) : QObject(parent)
{

}

void UrlExtractor::getFromUrl(const QUrl& url, int attempts)
{
    if (attempts < 10) {
        QNetworkReply *reply = qnam.get(QNetworkRequest(QUrl(url)));
        connect(reply, &QNetworkReply::finished, [=]() {
            QString data(reply->readAll());
            reply->deleteLater();
            QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
            if (reply->error() != QNetworkReply::NoError) {
                emit error("Network error: " + reply->errorString());
            } else if (!redirectionTarget.isNull()) {
                getFromUrl(redirectionTarget.toUrl(), attempts + 1);
            } else {
                emit finished(data);
            }
        });
    } else {
        emit error("Network error: redirect loop");
    }
}
