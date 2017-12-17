#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T10:00:07
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mySerialPort
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spccom.cpp

HEADERS  += mainwindow.h \
    spccom.h \
    common.h

FORMS    += mainwindow.ui

RESOURCES += \
    switch.qrc

DISTFILES +=
