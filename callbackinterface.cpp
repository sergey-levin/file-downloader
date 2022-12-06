#include "callbackinterface.h"

#include <QDebug>

void DownloaderInterface::onDownloadError(const QString &message)
{
    qInfo() << "Download failed with error:" << message;
}

void DownloaderInterface::onSaveError(const QString &message)
{
    qInfo() << "Failed to save file:" << message;
}

void DownloaderInterface::onStart(const QString &message)
{
    qInfo() << "Starting download:" << message;
}

void DownloaderInterface::onSuccess(const QString &message)
{
    const int size = message.toInt();
    qInfo() << "Downloaded total:" << size << "byte(s)";
}

void DownloaderInterface::onDownload(const QString &message)
{
    const int size = message.toInt();
    qInfo() << "Downloaded:" << size << "byte(s)";
}

void DownloaderInterface::onSave(const QString &message)
{
    qInfo() << "File saved:" << message;
}
