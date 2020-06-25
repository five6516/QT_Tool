QT -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
DEFINES += PYTHONSCRIPTLIB_LIBRARY

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
include($$PWD/../../lib_compile.pri)
#DLLDESTDIR = $$DLLDESTDIR/Script
#DESTDIR = $$DLLDESTDIR

SOURCES += \
    PythonScriptLib.cpp

HEADERS += \
    PythonScriptLib_global.h \
    PythonScriptLib.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


## python环境路径 3.7.3
win32 {
   INCLUDEPATH += $$PWD\include
   LIBS += -L$$PWD\libs -lpython37
   DEPENDPATH += $$PWD\libs
}
