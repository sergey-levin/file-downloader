#include "downloader.h"
#include "callbackinterface.h"

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QEventLoop>
#include <QTimer>
#include <QThreadPool>
#include <QtConcurrent/QtConcurrentMap>
#include <QDebug>

namespace {

qsizetype download(CallbackInterface &interface, QUrl url, QString dir, int timeout) {
    // TODO: Implement different Worker types to do something new
    auto worker = new Downloader(url, dir, interface);
    QEventLoop loop;
    QObject::connect(worker, &Downloader::downloaded, &loop, &QEventLoop::quit);
    if (timeout)
        QTimer::singleShot(1000 * timeout, &loop, &QEventLoop::quit);
    loop.exec(QEventLoop::ExcludeUserInputEvents);
    qsizetype result = worker->bytesDownloaded();
    worker->deleteLater();
    return result;
}

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setApplicationName("file-downloader");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("File downloader");
    parser.addHelpOption();
    parser.addVersionOption();

    // TODO: Make translation
    QCommandLineOption urlListOption(QStringList() << "l" << "url-list",
                                     QCoreApplication::translate("main", "Download files into <dir>."),
                                     QCoreApplication::translate("main", "urls"));
    parser.addOption(urlListOption);
    QCommandLineOption dirOption(QStringList() << "d" << "dir",
                                 QCoreApplication::translate("main", "Target directory."),
                                 QCoreApplication::translate("main", "directory"));
    parser.addOption(dirOption);
    QCommandLineOption timeoutOption(QStringList() << "t" << "timeout",
                                 QCoreApplication::translate("main", "Timeout to wait (sec)."),
                                 QCoreApplication::translate("main", "time"));
    parser.addOption(timeoutOption);
    QCommandLineOption connectionsOption(QStringList() << "c" << "connections",
                                     QCoreApplication::translate("main", "The number of parallel connections."),
                                     QCoreApplication::translate("main", "connections"));
    parser.addOption(connectionsOption);

    parser.process(a);

    // TODO: Validate input
    const QStringList urls = parser.value(urlListOption).split(" ", Qt::SkipEmptyParts);
    if (!urls.isEmpty()) {
        DownloaderInterface interface;

        const QString dir = parser.value(dirOption).isEmpty() ? "." : parser.value(dirOption);
        const int timeout = parser.value(timeoutOption).toInt();
        const int connections = qMax(1, parser.value(connectionsOption).toInt());
        auto pool = QThreadPool::globalInstance();
        pool->setMaxThreadCount(connections);
        QFuture<qsizetype> future = QtConcurrent::mappedReduced(
                pool,
                urls,
                [dir, timeout, &interface](const QString &url){
                    // Runs in thread from thread pool
                    return download(interface, url, dir, timeout);
                },
                [](qsizetype &total, const qsizetype &current) {
                    total += current;
                });
        future.waitForFinished();
        interface.onSuccess(QString::number(future.result()));
        qApp->quit();
    }

    // TODO: Different return codes
    return 0;
}
