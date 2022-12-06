#include "downloader.h"
#include "callbackinterface.h"

#include <QNetworkReply>
#include <QSaveFile>

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

Downloader::Downloader(QUrl url, QString target, CallbackInterface &interface, QObject *parent)
    : QObject(parent)
    , m_interface(interface)
    , m_target(target + '/' + url.fileName())
{
    connect(&m_fetcher, &QNetworkAccessManager::finished, this, &Downloader::onDownloaded);
    m_interface.onStart(url.toString());
    QNetworkRequest request(url);
    m_fetcher.get(request);
}

Downloader::~Downloader() {
}

void Downloader::onDownloaded(QNetworkReply *reply)
{
    if (isSucceeded(reply)) {
        const QByteArray data = reply->readAll();
        m_size = data.size();
        m_interface.onDownload(QString::number(m_size));

        QSaveFile file(m_target);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(data);
            file.commit();
            m_interface.onSave(m_target);
        } else {
            m_interface.onSaveError(m_target);
        }
    } else {
        m_interface.onDownloadError(reply->errorString());
    }
    reply->deleteLater();
    emit downloaded();
}

