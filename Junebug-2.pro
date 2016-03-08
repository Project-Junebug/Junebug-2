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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/cryptopp/ -lcryptopp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/cryptopp/ -lcryptopp
else:unix: LIBS += -L$$PWD/cryptopp/ -lcryptopp

INCLUDEPATH += $$PWD/cryptopp
DEPENDPATH += $$PWD/cryptopp
