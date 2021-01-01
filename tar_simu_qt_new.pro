QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CFLAGS += -fexec-charset=GBK -finput-charset=UTF-8
QMAKE_CXXFLAGS += -fexec-charset=GBK -finput-charset=UTF-8

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Archive.cpp \
    Block.cpp \
    Compress.cpp \
    ConvertGBK.cpp \
    Decompress.cpp \
    Header.cpp \
    HuffmanTree.cpp \
    interface.cpp \
    mainwindow.cpp \
    multifiledialog.cpp \
    multifiledirdialog.cpp

HEADERS += \
    Archive.h \
    Block.h \
    Compress.h \
    ConvertGBK.h \
    Decompress.h \
    Header.h \
    HuffmanTree.h \
    mainwindow.h \
    multifiledialog.h \
    multifiledirdialog.h

FORMS += \
    mainwindow.ui \
    multifiledialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
