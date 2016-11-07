#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T20:00:23
#
#-------------------------------------------------

QT       += core gui serialport

CONFIG   += qscintilla2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = casiofx8x0p
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    baudrate.cpp \
    casiobasichelper.cpp

HEADERS  += mainwindow.h \
    baudrate.h \
    casiobasichelper.h

FORMS    += mainwindow.ui

DISTFILES += \
    LICENSE
