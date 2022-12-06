#pragma once

#include <QString>

/**
 * @brief The CallbackInterface class implements callbacks interface. All methods should be threadsafe.
 */
class CallbackInterface
{
public:
    CallbackInterface() {}
    virtual ~CallbackInterface() {}
    virtual void onDownloadError(const QString &message) = 0;
    virtual void onSaveError(const QString &message) = 0;
    virtual void onStart(const QString &message) = 0;
    virtual void onSuccess(const QString &message) = 0;
    virtual void onDownload(const QString &message) = 0;
    virtual void onSave(const QString &message) = 0;
};

/**
 * @brief The DownloaderInterface class implements file downloader interface. All methods are threadsafe.
 */
class DownloaderInterface : public CallbackInterface
{
public:
    virtual void onDownloadError(const QString &message);
    virtual void onSaveError(const QString &message);
    virtual void onStart(const QString &message);
    virtual void onSuccess(const QString &message);
    virtual void onDownload(const QString &message);
    virtual void onSave(const QString &message);
};

