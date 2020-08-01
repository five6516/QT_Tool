QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
DEFINES += QT_PLUGIN_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include($$PWD/../../plugin_compile.pri)


SOURCES += \
    DownloadForm.cpp \
    Form.cpp \
    InformationDialog.cpp \
    QT_Plugin.cpp \
    curlPackage/curlSFTP.cpp

HEADERS += \
    DownloadForm.h \
    Form.h \
    InformationDialog.h \
    QT_Plugin.h \
    curlPackage/curlData.h \
    curlPackage/curlSFTP.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    DownloadForm.ui \
    Form.ui \
    InformationDialog.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/curl/ -llibcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/curl/ -llibcurl

INCLUDEPATH += $$PWD/curl
DEPENDPATH += $$PWD/curl
