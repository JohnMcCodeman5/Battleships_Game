QT       += core gui network
QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/Klijent.cpp \
    source/Multiplayer.cpp \
    source/Singleplayer.cpp \
    source/Tajmer.cpp \
    source/partija.cpp \
    source/Tabla.cpp \
    source/Brod.cpp \
    source/Sudija.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/popup.cpp

HEADERS += \
    include/Klijent.h \
    include/Multiplayer.h \
    include/Singleplayer.h \
    include/Tabla.h \
    include/Brod.h \
    include/Sudija.h \
    include/Tajmer.h \
    include/mainwindow.h \
    include/partija.h \
    include/popup.h

FORMS += \
    forms/mainwindow.ui \
    forms/partija.ui \
    forms/popup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    sounds.qrc

