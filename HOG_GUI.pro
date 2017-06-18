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
    testingdialog.cpp \
    gradient.cpp \
    dataReader.cpp \
    neuralNetwork.cpp \
    neuralNetworkTrainer.cpp

HEADERS  += object_classifier.h \
    trainingdialog.h \
    testingdialog.h \
    neuralNetwork.h \
    dataReader.h \
    globaldefs.h \
    gradient.h \
    neuralNetworkTrainer.h \
    dataEntry.h

FORMS    += object_classifier.ui \
    trainingdialog.ui \
    testingdialog.ui

INCLUDEPATH += "C:\Program Files\OpenCV-3.2.0\opencv\build\include"
LIBS += -L"C:\Program Files\OpenCV-3.2.0\opencv-build_x64\lib\Release" \
    -lopencv_core320 \
    -lopencv_highgui320 \
    -lopencv_imgcodecs320 \
    -lopencv_imgproc320 \
    -lopencv_features2d320 \
    -lopencv_calib3d320

DISTFILES += \
    HOG_GUI.pro.user

RESOURCES += \
    resorces.qrc

