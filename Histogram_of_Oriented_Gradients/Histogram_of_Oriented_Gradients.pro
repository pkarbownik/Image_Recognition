#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T10:20:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Histogram_of_Oriented_Gradients
TEMPLATE = app


SOURCES += main.cpp\
        gradient.cpp

HEADERS  += gradient.h

FORMS    += gradient.ui

INCLUDEPATH += C:\Qt\opencv_build_for_qt_mingw_5_3\install\include
LIBS += -LC:\Qt\opencv_build_for_qt_mingw_5_3\install\x86\mingw\lib \
    -lopencv_core320.dll \
    -lopencv_highgui320.dll \
    -lopencv_imgcodecs320.dll \
    -lopencv_imgproc320.dll \
    -lopencv_features2d320.dll \
    -lopencv_calib3d320.dll
