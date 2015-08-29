#-------------------------------------------------
#
# Project created by QtCreator 2015-08-23T19:04:48
#
#-------------------------------------------------

QT       += core gui\
            multimedia\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ../
TARGET = FlowFree_client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamescene.cpp \
    gameview.cpp \
    gamesolver.cpp

HEADERS  += mainwindow.h \
    gamescene.h \
    gameview.h \
    gamesolver.h

FORMS  += mainwindow.ui

RESOURCES += res.qrc
