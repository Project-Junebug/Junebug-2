#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T14:22:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Junebug-2
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    pagelist.cpp \
    lib.cpp

HEADERS  += mainwindow.h \
    pagelist.h \
    lib.h
FORMS    += mainwindow.ui

unix|win32: LIBS += -L$$PWD/../build-cryptopp-Desktop_Qt_5_5_1_MinGW_32bit-Release/release/ -lcryptopp

INCLUDEPATH += $$PWD/cryptopp
DEPENDPATH += $$PWD/cryptopp

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../build-cryptopp-Desktop_Qt_5_5_1_MinGW_32bit-Release/release/cryptopp.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../build-cryptopp-Desktop_Qt_5_5_1_MinGW_32bit-Release/release/libcryptopp.a
