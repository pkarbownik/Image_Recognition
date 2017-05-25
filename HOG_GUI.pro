#-------------------------------------------------
#
# Project created by QtCreator 2017-05-21T19:09:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HOG_GUI
TEMPLATE = app


SOURCES += main.cpp\
        object_classifier.cpp \
    trainingdialog.cpp \
    testingdialog.cpp

HEADERS  += object_classifier.h \
    trainingdialog.h \
    testingdialog.h

FORMS    += object_classifier.ui \
    trainingdialog.ui \
    testingdialog.ui

RESOURCES +=

DISTFILES +=
