#pragma once

#include <QObject>

/**
 * @brief The Downloader class implements multithreaded urls downloader
 */
class Downloader final : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(const QStringList &urls,
                        QString dir,
                        int timeout,
                        int connections,
                        QObject *parent = nullptr);
};
