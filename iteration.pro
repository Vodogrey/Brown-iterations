QT += core gui widgets

TARGET = iteration
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    calculation.cpp

HEADERS += \
    mainwindow.h \
    calculation.h

