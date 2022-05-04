#-------------------------------------------------
#
# Project created by QtCreator 2022-05-01T08:55:19
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UniRemoteController
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    commands.cpp \
    commandstablemodel.cpp \
    fileutils.cpp \
    aboutdialog.cpp \
    settingsdialog.cpp \
    addcommanddialog.cpp

HEADERS += \
        mainwindow.h \
    commands.h \
    commandstablemodel.h \
    fileutils.h \
    aboutdialog.h \
    settingsdialog.h \
    addcommanddialog.h \
    settingsstruct.h

FORMS += \
        mainwindow.ui \
    aboutdialog.ui \
    settingsdialog.ui \
    addcommanddialog.ui

RESOURCES += \
    uniremotecontroller.qrc


