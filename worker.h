#pragma once

#include <QNetworkAccessManager>

/**
 * @brief The Worker class implements downloading url to target dir
 */
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QUrl url, QString target, QObject *parent = 0);
    virtual ~Worker();
    qsizetype bytesDownloaded() const { return m_size; }

signals:
    void downloaded();

private slots:
    void onDownloaded(QNetworkReply *reply);

private:
    QNetworkAccessManager m_fetcher;
    QString m_target;
    qsizetype m_size {0};
};
