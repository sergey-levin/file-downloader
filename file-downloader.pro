
!greaterThan(QT_MAJOR_VERSION, 5) {
    message("Cannot build $$TARGET with Qt version $${QT_VERSION}.")
    error("Use Qt version 6 or above.")
}

QT -= gui

QT += network concurrent

CONFIG += c++17 console
CONFIG -= app_bundle

HEADERS += \
    callbackinterface.h \
    downloader.h \

SOURCES += \
    callbackinterface.cpp \
    downloader.cpp \
    main.cpp \

OTHER_FILES += \
    readme.md \

