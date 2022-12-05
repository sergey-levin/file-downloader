#include "downloader.h"
#include "worker.h"

#include <QCoreApplication>
#include <QEventLoop>
#include <QTimer>
#include <QThreadPool>
#include <QtConcurrent/QtConcurrentMap>

#include <QDebug>

namespace {

qsizetype download(QUrl url, QString dir, int timeout) {
    // TODO: Implement different Worker types to do something new
    auto worker = new Worker(url, dir);
    QEventLoop loop;
    QObject::connect(worker, &Worker::downloaded, &loop, &QEventLoop::quit);
    if (timeout)
        QTimer::singleShot(1000 * timeout, &loop, &QEventLoop::quit);
    loop.exec(QEventLoop::ExcludeUserInputEvents);
    qsizetype result = worker->bytesDownloaded();
    worker->deleteLater();
    return result;
}

}

Downloader::Downloader(const QStringList &urls, QString dir, int timeout, int connections, QObject *parent)
    : QObject(parent)
{
    // Simple input validation
    if (urls.isEmpty())
        return;
    dir = dir.isEmpty() ? "." : dir;
    connections = qMax(1, connections);

    auto pool = QThreadPool::globalInstance();
    pool->setMaxThreadCount(connections);
    QFuture<qsizetype> future = QtConcurrent::mappedReduced(
            pool,
            urls,
            [dir, timeout](const QString &url){
                // Runs in thread from thread pool
                return download(url, dir, timeout);
            },
            [](qsizetype &total, const qsizetype &current) {
                total += current;
            });
    future.waitForFinished();
    qInfo() << "Downloaded total:" << future.result() << "byte(s)";
    qApp->quit();
}

