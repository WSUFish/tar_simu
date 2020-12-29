QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    interface.cpp \
    mainwindow.cpp \
    Archive.cpp \
    Block.cpp \
    Compress.cpp \
    ConvertGBK.cpp \
    Decompress.cpp \
    Header.cpp \
    HuffmanTree.cpp

HEADERS += \
    mainwindow.h \
    Archive.h \
    Block.h \
    Compress.h \
    ConvertGBK.h \
    Decompress.h \
    Header.h \
    HuffmanTree.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
