
# Urls Downloader

This command line tool is an example of multi threaded urls downloader using QtConcurrent.

## Compile Requirements

Qt 6.3 or above.

## Usage

Command line parameters:
* -l, --url-list - array or urls to download. Required.
* -d, --dir - directory to save downloaded files. Current directory if not provided.
* -t, --timeout - timeout in seconds to wait a single download. Infinite if not provided.
* -c, --connections - number of parallel downloads. One if not provided.

## Example

    file-downloader --connections 4 --url-list "https://doc.qt.io/qtcreator/images/qtcreator-textfinder-screenshot.png https://doc.qt.io/qtcreator/images/qtcreator-new-qt-gui-application.png https://doc.qt.io/qtcreator/images/qtcreator-intro-and-location-qt-gui.png https://doc.qt.io/qtcreator/images/qtcreator-textfinder-contents.png https://doc.qt.io/qtcreator/images/creator_android_tutorial_ex_app.png https://doc.qt.io/qtcreator/images/qtquick-mobile-tutorial-manifest.png"

