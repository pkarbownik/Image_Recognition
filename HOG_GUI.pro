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

INCLUDEPATH += C:\Qt\opencv_build_for_qt_mingw_5_3\install\include
LIBS += -LC:\Qt\opencv_build_for_qt_mingw_5_3\install\x86\mingw\lib \
    -lopencv_core320.dll \
    -lopencv_highgui320.dll \
    -lopencv_imgcodecs320.dll \
    -lopencv_imgproc320.dll \
    -lopencv_features2d320.dll \
    -lopencv_calib3d320.dll

DISTFILES +=

RESOURCES += \
    resorces.qrc

