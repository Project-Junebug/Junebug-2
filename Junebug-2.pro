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
    initquestions.ignore.cpp \
    lib.cpp \
    QuestionBase.cpp \
    QuestionCheckbox.cpp \
    QuestionInfo.cpp \
    QuestionList.cpp

HEADERS  += mainwindow.h \
    hash.h \
    lib.h \
    QuestionBase.h \
    QuestionCheckbox.h \
    QuestionInfo.h \
    QuestionList.h
FORMS    += mainwindow.ui

win32:RC_ICONS += icon.ico
