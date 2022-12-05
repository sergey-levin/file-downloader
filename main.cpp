#include "downloader.h"

#include <QCoreApplication>
#include <QCommandLineParser>

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
    const QString dir = parser.value(dirOption);
    const int timeout = parser.value(timeoutOption).toInt();
    const int connections = parser.value(connectionsOption).toInt();

    Downloader(urls, dir, timeout, connections);

    // TODO: Different return codes
    return 0;
}
