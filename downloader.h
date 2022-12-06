#pragma once

#include <QNetworkAccessManager>

class CallbackInterface;

/**
 * @brief The Downloader class implements downloading url to target dir
 */
class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QUrl url, QString target, CallbackInterface &interface, QObject *parent = 0);
    virtual ~Downloader();
    qsizetype bytesDownloaded() const { return m_size; }

signals:
    void downloaded();

private slots:
    void onDownloaded(QNetworkReply *reply);

private:
    CallbackInterface &m_interface;
    QNetworkAccessManager m_fetcher;
    QString m_target;
    qsizetype m_size {0};
};
