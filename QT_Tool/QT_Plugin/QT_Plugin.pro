TEMPLATE = subdirs

SUBDIRS += \
    QT_Plugin_Server \
    QT_Plugin_Encryption \
    QT_Plugin_JsonFormat \
    QT_Plugin_Download \

CONFIG(release, debug|release){
SUBDIRS += \
    QT_Plugin_Python
}
