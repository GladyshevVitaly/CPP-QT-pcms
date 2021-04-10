#-------------------------------------------------
#
# Project created by QtCreator 2014-04-01T09:33:00
#
#-------------------------------------------------

QT       += core gui

QT           += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pcms
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form_about.cpp \
    formoptions.cpp \
    sleeplength.cpp

HEADERS  += mainwindow.h \
    form_about.h \
    formoptions.h \
    sleeplength.h

FORMS    += mainwindow.ui \
    form_about.ui \
    formoptions.ui \
    sleeplength.ui

RESOURCES += \
    pcmsRes.qrc

CONFIG += console
