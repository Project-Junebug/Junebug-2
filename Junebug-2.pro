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
    initquestions.ignore.cpp \
    lib.cpp

HEADERS  += mainwindow.h \
    pagelist.h \
    hash.h \
    lib.h
FORMS    += mainwindow.ui
