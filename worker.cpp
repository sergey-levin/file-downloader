
#include "worker.h"

#include <QNetworkReply>
#include <QSaveFile>

#include <QDebug>

namespace {

bool isSucceeded(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError ) {
        const int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if ((code >=200) && (code < 300)) {
            return true;
        }
    }
    return false;
}

}

Worker::Worker(QUrl url, QString target, QObject *parent)
    : QObject(parent)
    , m_target(target + '/' + url.fileName())
{
    connect(&m_fetcher, &QNetworkAccessManager::finished, this, &Worker::onDownloaded);
    qInfo() << "Starting download:" << url;
    QNetworkRequest request(url);
    m_fetcher.get(request);
}

Worker::~Worker() {}

void Worker::onDownloaded(QNetworkReply *reply)
{
    if (isSucceeded(reply)) {
        const QByteArray data = reply->readAll();
        m_size = data.size();
        qInfo() << "Downloaded:" << m_size << "byte(s)";

        QSaveFile file(m_target);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(data);
            file.commit();
            qInfo() << "File saved:" << m_target;
        } else {
            qInfo() << "Failed to save file:" << m_target;
        }
    } else {
        qInfo() << "Download failed with error:" << reply->errorString();
    }
    reply->deleteLater();
    emit downloaded();
}

